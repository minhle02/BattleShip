# BattleShip
<p>This is an one player version of Battle Ship game. 
Ships are randomly generated and placed on board. Player can review their ship arrangment in Ships tab.
The Firing tab are used to fire at the opponent.</p>
<hr>
<p>This game are designed based on Model/View Programming. 
Classes DisplayPlayer, FiringTab, and ShipBoard are responsible for displaying contents to user (View Component), 
while Player classes contains all the necessary data and performs back-end calculations (Model component). 
<p>This game is also configured to use Cmake to build the program, thus allows IDE others than Qt Creator to inspect and build the program.</p>
<p>Note: In the following file <pre>CMakeLists.txt</pre> Please change the path in <code>CMAKE_PREFIX_PATH</code> to the folder that contains CMake configuration in Qt folder in your computer.
It usually has path looks something like <code>....Qt/6.2.1/macos/lib/cmake</code></p>
<hr>
<div>Icons made by <a href="https://www.freepik.com" title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a></div>
