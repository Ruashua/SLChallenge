# My OBS interface project

Building should be pretty simple.  It requires node-gyp.

## Prerequisites

A compiled OBS build needs to be in the folder ./obs/obs-studio such that all of the release 
DLLs can be found in ./obs/obs-studio/build/rundir/Release/bin/64bit/obs.dll

## Initializing and running the package

Here are the commands needed to initialize and run the package.

npm init
npm install
npm start

## Notes
This was a lot of fun interacting with the OBS API.  I have been streaming for a while, so this was an exciting 
opportunity.  I love learning new things, especially when they pertain to my interests.

Getting the environment setup on my computer was a bit of a challenge!  There was a lot of prerequisites
I needed to install on my computer.  Then getting OBS to build was interesting.  A header
file reference in aja in OBS was incorrect.  And the vs project built from cmake was missing a .lib I 
had to put in there.  Most of the guides on how to build OBS from scratch are either not very verbose, or outdated.
I figured it out in the end.

I tried to do as many extras as I could, but I believe my build might have been slightly setup incorrectly.
I stopped at trying to start the output to Twitch.  When I called

> obs_output_create("null_output", "null", nullptr, nullptr);

node.js was giving me a an error in the console window:

> [23080:0517/131944.996:ERROR:crashpad_client_win.cc(868)]

Attaching the VS debugger to the process, I found that the obs_output_create was causing a memory
access violation in obs.dll.  That exact obs_output_create line I got from OBS's source code.  It should be a proven 
function call.  
I debugged my build of OBS separately and every time it called obs_output_create it 
succeeded.  This all leads me to believe that I have a slight build environment issue.  
This issue could be alleviated by trying to collaborate with team members, contacting OBS members, 
communicating on their discord, etc.  It may also be prevented with a step by step setup environment 
document or script to have my machine in a proven working state.

Thank you
