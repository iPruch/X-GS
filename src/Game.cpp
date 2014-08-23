#include <X-GS/Game.hpp>

#include "ResourcePath.hpp" // Not provided with X-GS. 

namespace xgs {
    
	// Constructor
    Game::Game()
    : mWindow(sf::VideoMode(200, 200), "Window Title", sf::Style::Close)
	, mTimeSinceStart(0)
	, mStatisticsNumFrames(0)
	, mStatisticsUpdateTime(0)
	, mVSync(true)
	, mSceneManager(mWindow)
    {
        // Resource loading here if needed (RAII)
		
		// Set some mWindow's properties
        mWindow.setVerticalSyncEnabled(mVSync);
		mWindow.setKeyRepeatEnabled(false); // Disable key repeat when holding a key as this behavior is unwanted for games
		sf::View view = mWindow.getView();
		view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
		//mWindow.setView(view);
		
        // Statistics
        mFont.loadFromFile(resourcePath() + "Sansation.ttf"); // resourcePath() method needs an implementation per platform/OS
        mStatisticsText.setFont(mFont);
        mStatisticsText.setPosition(5.f, 5.f);
        mStatisticsText.setCharacterSize(14);
        mStatisticsText.setColor(sf::Color::Green);
		
		// Register the example scenes in the Scene Manager
		mSceneManager.registerScene<ExampleScene>(Scenes::Example);
		mSceneManager.registerScene<ExampleScene2>(Scenes::Example2);
		
		// And load the first one
		mSceneManager.loadScene(Scenes::Example);
    }
    
	
	
    void Game::update(const HiResDuration& dt)
    {
        
        // Update calls here
        
        // Example:
        /*
         for (auto &entity : entitiesContainer) {
         
         // Advance the simulation/physics integrating
         // Choose Euler, RK4 or implement your own
         Integrator::Euler(entity.state, dt);
         //Integrator::RK4(entity.state, dt);
         
         // Call each entity's own update method
         entity.update(dt);
         }
		 
		 NOTE:
		 The recommended approach is to ask the Scene Manager to update
		 itself, which will invoke the current scene's update method.
		 This is the default implementation:
         */
		
		mSceneManager.update(dt);
        
    }
    
    void Game::render()
    {
        mWindow.clear();
        
        // Draw calls here
        
        // Example:
        /*
         for (auto &entity : entitiesContainer) {
         // Call each entity's own draw method
         entity.draw(dt);
         }
		 
		 NOTE:
		 The recommended approach is to ask the Scene Manager to render
		 itself, which will invoke the current scene's render method.
		 This is the default implementation:
         */

        mSceneManager.render();

		mWindow.draw(mStatisticsText); // Comment this line to hide statistics
		
        mWindow.display();
    }
    
    void Game::updateStatistics(const HiResDuration& elapsedTime)
    {
        mStatisticsUpdateTime += elapsedTime;
        mStatisticsNumFrames += 1;
        
        if (mStatisticsUpdateTime >= ONE_SECOND)
        {
            mStatisticsText.setString(
                                      "Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
                                      "Time / Update = " + std::to_string((float)mStatisticsUpdateTime.count()/mStatisticsNumFrames/1000000) + "ms" + "\n"
                                      + "V-Sync enabled: " + (mVSync ? "Yes" : "No") + "\n"
                                      + "Number of objects: To be implemented"); // + toString(entitiesContainer.count()));
            
            mStatisticsUpdateTime -= ONE_SECOND;
            mStatisticsNumFrames = 0;
        }
    }

	
	
    /*****************************************/
    /***             TIMESTEPS             ***/
    /*****************************************/
    
    
    /* --------------------------
     * Basic Fixed Delta Timestep
     * --------------------------
     *
     * Updates as fast as it can at a fixed frame time.
     * If it is faster than the display frequency and V-sync is disabled -> Faster simulation
     * If the computer is slow and can't update at the specified frame time -> Slower simulation
     *
     * Uses: With V-Sync activated, good for mobile platforms, where system events (notifications,
     * updates, incomming call...) may break the game experience. As with this kind of timestep
     * the game would slowdown instead of render at low fps but advance the game world at a normal
     * time, the player can react better to these system events interruptions.
     */
    
    void Game::runFixedDeltaTime()
    {
        HiResDuration simulationFixedDuration(ONE_SECOND/60); // Simulation step
        
        HiResDuration lastRenderDuration; // FrameTime (aka dt)
        
        HiResTime lastTimeMeasure = HiResClock::now();
        HiResTime newTimeMeasure;
        
        while (mWindow.isOpen())
        {
            newTimeMeasure = HiResClock::now();
            lastRenderDuration = newTimeMeasure - lastTimeMeasure;
            lastTimeMeasure = newTimeMeasure;
            
            // Input handling call here
            
            update(simulationFixedDuration);
            mTimeSinceStart += simulationFixedDuration;
            
            updateStatistics(lastRenderDuration);
            
            render();
        }
    }
    
    
    
    /* -----------------------------
     * Basic Variable Delta Timestep
     * -----------------------------
     *
     * Updates as fast as it can with no specified frame time.
     * If it is faster than the display frequency and V-sync is disabled -> No problems. Normal simulation
     * If it the computer is slow and fps are low -> Normal simulation, but big steps can break the physics
     *
     * Uses: General
     * Needs high resolution time compatibility (hardware/OS)
     */
    
    void Game::runVariableDeltaTime()
    {
        HiResDuration lastRenderDuration(0); // FrameTime (aka dt)
        
        HiResTime lastTimeMeasure = HiResClock::now();
        HiResTime newTimeMeasure;
        
        while (mWindow.isOpen())
        {
            newTimeMeasure = HiResClock::now();
            lastRenderDuration = newTimeMeasure - lastTimeMeasure;
            lastTimeMeasure = newTimeMeasure;
            
            // Input handling call here
            
            update(lastRenderDuration);
            mTimeSinceStart += lastRenderDuration;
            
            updateStatistics(lastRenderDuration);
            
            render();
        }
    }
    
    
	
    
    /* -------------------------
     * Semi Fixed Delta Timestep
     * -------------------------
     *
     * Updates the simulation with an upper bound. This ensures the simulation
     * won't be oversampled if vSync is disabled and the simulation completes
     * faster than the display rate.
     * If X seconds of simulation takes Y seconds of real time, with Y > X, the
     * simulation will slowdown. That can be an acceptable behavior on heavy
     * load spikes, but this should be only temporary and not taken as normal.
     *
     * Uses: General
     * Needs high resolution time compatibility (hardware/OS)
     */
    
    void Game::runSemiFixedDeltaTime()
    {
        HiResDuration simulationFixedDuration(ONE_SECOND/60); // FrameTime (aka dt)
        
        const short multipleStepLimit = 3; // Limit of steps to consume the frameTime. Needed to avoid the spiral of death effect. Tunning is needed
        short multipleStepCounter = 0;
        
        HiResDuration lastRenderDuration;
        HiResDuration simulationDuration;
        
        HiResTime lastTimeMeasure = HiResClock::now();
        HiResTime newTimeMeasure;
        
        while (mWindow.isOpen())
        {
            newTimeMeasure = HiResClock::now();
            lastRenderDuration = newTimeMeasure - lastTimeMeasure;
            lastTimeMeasure = newTimeMeasure;
            
            updateStatistics(lastRenderDuration); // Update statistics before the variable gets modified
            
            while (lastRenderDuration > HiResDuration::zero() && multipleStepCounter <= multipleStepLimit)
            {
                simulationDuration = std::min(lastRenderDuration, simulationFixedDuration);
                
                // Input handling call here
                
                update(simulationDuration);
                
                lastRenderDuration -= simulationDuration;
                mTimeSinceStart += simulationDuration;
                ++multipleStepCounter;
            }
            multipleStepCounter = 0;
            
            
            render();
        }
    }
    
    
    
    /* ------------------------------------------------------
     * Fixed Delta Timestep with variable rendering framerate
     * ------------------------------------------------------
     *
     * Simulation and Rendering become decoupled. This can be seen as a producer-consumer model,
     * where the Renderer produces (the time it takes) and the Simulation consumes that time
     * in fixed dt chunks.
     * If Rendering FPS is not divisible by the Simulation frequency, a tiny temporal aliasing can appear.
     * To solve it, enable VSync and set simulationFixedDuration to the display Hz or implement interpolation.
     *
     * Uses: General, deterministic simulations (different runs with the same result), network-related games
     * Needs high resolution time compatibility (hardware/OS)
     */
    
    void Game::runFixedSimulationVariableFramerate()
    {
        HiResDuration accumulatedRenderTime(0); // Accumulator of render time to be consumed for simulations
        HiResDuration simulationFixedDuration(ONE_SECOND/60); // This determines the Simulation frequency (60 Hz now)
        
        HiResDuration lastRenderDuration; // FrameTime
        
        HiResTime lastTimeMeasure = HiResClock::now();
        HiResTime newTimeMeasure;
        
        while (mWindow.isOpen())
        {
            newTimeMeasure = HiResClock::now();
            lastRenderDuration = newTimeMeasure - lastTimeMeasure;
            lastTimeMeasure = newTimeMeasure;
            
            accumulatedRenderTime += lastRenderDuration;
            
            while (accumulatedRenderTime >= simulationFixedDuration)
            {
                accumulatedRenderTime -= simulationFixedDuration;
                
                // Input handling call here
                
                update(simulationFixedDuration);
                
                mTimeSinceStart += simulationFixedDuration;
            }
            
            updateStatistics(lastRenderDuration);
            
            render();
        }
    }
} // namespace xgs
