# Blockland - GhostLimitBypass DLL
Oops, made the title different than what it actually is... <br>
Makes networking with all ghosting objects a little different. <br><br>
Unfortunately, I do not really see a change in networking/ghosting. Function still returns 1 even with the old dll. Maybe I don't know what it really does. Check out https://github.com/Electrk/PackageAnyFunction, then do **function NetConnection::getFinishedInitialGhost(%obj) { return 0; }** and I believe it should work the same way unless I misunderstand GhostLimitBypass DLL.
