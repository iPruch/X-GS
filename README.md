X-GS (Cross-platform Game Skeleton)
-----------------------------------

This is a brief introducction and description of what is X-GS. I'll keep updating this Readme file to clarify things, give details, instructions, motivation behind this project, etc.


### What is X-GS?

X-GS stands for Cross-platform Game Skeleton, which I expect to sound more like "this is a template for the core of your game" more than "this is the best game engine of all-time!".

It is written in C++ with one idea in mind: Efficiency. C++ is known for being very efficient and for having a very robust standard library. It appeared in 1983, but it still used on a wide range of fields, specially those where every bit of performance matters (as you can guess, video games is one of these fields). I'm about to get my degree at IT, so I'm kind of newbie. I haven't learnt C++ at the University and it looks pretty difficult at first. Some C++ books after, my opinion hasn't changed. I have to practise, make mistakes and learn from them. Maybe it's hasty to get that practise doing my end-of-degree project, but I'll try. Oh, well, probably I should have started from there: Yes, *X-GS is my end-of-degree project*.

The other important pilar of X-GS is SFML (Simple and Fast Multimedia Library). Think of it as a collection of primitives to work with graphics, audio, network, input, etc. For those who know SDL, it is some sort of new and object-oriented SDL with a lot of improvements (I'll look for some benchmakrs and post them here) and great modularity, structure and organization. Also, it provides the 'X' of the title: Code is cross-platform as SFML gives an API which abstracts the SO-specific details. Linux, Mac OS X and Windows are the current supported platforms by SFML. They are a great team with an active community, and they are working hard to make SFML compatible with iOS and Android.

But C++ and SFML by themselves doesn't give you a game loop, an Entity (or GameObject for Unity fans), nor a scene graph, physics, etc. A game engine has many definitions and there's a lot of discussions about what exactly is a game engine. For me, it is a collection of useful tools which helps a developer to focus on making a game as the low level details are already implemented and hidden to the user.


### Then, is X-GS a game engine?

No. Forget about Unity or UDK. I am only one person, not a big team of experienced people making an enormous software monster. Besides, it isn't my intention.

As I tried to hint with the name (Game Skeleton), I want X-GS to serve more like a template for making games in C++ and SFML. This means that you can download the code, use it as the core and build your game around it. You can also modify it to fit your needs, or combine it with other external libraries to get more functionalities (don't reinvent the wheel! If you need a particle system or a physics engine, you can probably download a good one in C/C++ and add it easily to your project).

So, the basic idea with regard X-GS is to provide a basic structure and some basic functionalities that doesn't come with C++/SFML that you'd have to code from scratch.


### But C++ is old. Unity/UDK is better, so this project hasn't a point!

On the firs hand, C++ is a programming language that is constantly evolving. SFML is built with the best practices of modern C++ in mind and it uses some of the C++11 new standard features which makes it easier to use and more reliable. For example, using the RAII idiom (Resource Aquisition Is Initialization) and smart pointers make you think less of manual and error-prone memory management as it gets kind of automatic and leak-proof.

On the other hand, Unity/UDK/<put-your-favourite-engine-here> are truly great. In fact, I'm thinking of aquiring a license in a mid-term future and start making games for consoles and PC/Mac. But what if I only want to make a simple 2D game with minimum requirements? What if I want to target a platform which is not on the list of those engines (Nintendo 3DS, for example)? Maybe I want have a low-level detail control. Or maybe I can't afford a game engine license. In my opinion, these game engines are great to forget about details and start making games right now. Almost one click and your game is built for several platforms! BUT, you have to think of the future: What if the game engine you use gets discontinued? Or they deprecate/change something? Or even worse: What if you get too accustomed to a specific engine? You'll probably stop learning. Or you could get a new job where they don't use that engine.

Of course, X-GS isn't the panacea. But it can be the starting point of your own (or the company you work for) technology. It can also be the YAGNI touch your project needs. YAGNI stands for "You Ain't Gonna Need It", which means you have to focus on what you need and forget about everything else (for now). [Here] (http://stefan.boxbox.org/2013/02/10/game-development-design-2-good-habits-techniques-and-workflows/) you have a better explanation of YAGNI and other good habits and techniques.


### I want to download it and start making my game!

The deadline of my end-of-degree project is due for September, so I need to finish this project asap. That said, my objective is to get the fundamental part of X-GS working before that date. After that I'd probably extend it with some functionalities, but again: please, don't expect a full-of-nice-features engine as it is not the purpose. Think YAGNI!


### Milestones

If you want to see the milestones and what I'm working on, [here] (https://trello.com/b/JPZUbDz7/x-gs) is my Trello public board for this project.

