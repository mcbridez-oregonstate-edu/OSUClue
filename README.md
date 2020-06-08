# OSUClue
<h1>Overview</h1>
<p>This project is a desktop reproduction of the classic board game Clue! The goal of the project is to create a high-fidelity GUI implementation with multi-player capability. It also features server/client functionality, allowing multiple users to play with each other online.</p>

<h1>User Documentation</h1>
<h2>Main Features</h2>
<ul>
<li>GUI reproduction of Clue! including board, cards, and player notebooks</li>
<li>High fidelity to the rules of the original game.</li>
<li>Ability to play online with others via a server.</li>
<li>Installable game that creates a desktop shortcuts and a start menu folder</li>
</ul>

<h2>How to Play</h2>
<p>Download the installer from the latest release build. Run the installer. Install to your folder of choice. Run the game via desktop shortcut, start menu shortcut, or directly from the folder.</p>

<p>The server needs to enable port forwarding first (to port 3456). The following link will show how to do it.</p>

<p>https://www.noip.com/support/knowledgebase/general-port-forwarding-guide/</p>

<p>The clients must enter the server's IP address in order to connect. Upon connection, everyone is taken to the character select screen. After each player chooses a character, the game will start.</p>

<p><b>NOTE</b>: There may be a warning that the installer is from an untrusted source. The installer is completely safe. We are just unlisted as a trusted source.</p>

<h2>Quality Attributes</h2>
<h3>Usability</h3>
<p>This project aims to be simple and easily learnable. Installing the game follows standard procedure of running an installer. The GUI is relies on recognition rather than recall. The game's assets are all dispalyed by default. The controls are displayed on screen as well.</p>

<h3>Fidelity</h3>
<p>This project faithfully reproduces the game of Clue!. The game follows the rules of the board game. The board, player characters, and cards are all facsimiles to the board game's counterparts.</p>

<h3>Portability</h3>
<p>This project aims to be portable. There is no need for any special software. The installer will handle installation for any 32-bit Windows platform.</p>

<h1>System Documentation</h1>
<h2>Software Architecture and Design</h2>
<ul>
<li>An overview of your software’s architecture and design</li>
<li>At least 2 diagrams communicating the architecture/design of your software</li>
<li>Ability to play online with others via a server.</li>
<li>Design patterns, and in what modules/componnents</li>
</ul>

<h2>Final State of the Software</h2>
<p>The software uses a single MSI file to install the game onto a user's computer.</p>

<p>There is server/client functionality, allowing users to play with each other over the internet. The server and clients all use the same executable file. They only differ upon which starting menu option is selected.</p>

<p>The game is a GUI implementation of Clue!, closely mirroring the rules and play of the original board game. Users can follow the flow of the game by using the GUI. Users can also view their character portrait, name, cards, and notebooks at all times.</p>

<h2>Known Issues/Bugs</h2>
<ul>
<li>The installer may be flagged as an untrusted source.</li>
<li>The game may need to be run as an admin.</li>
  <li>The server needs to enable port forwarding. This may be a source of confusion for less technically inclined end users.</li>
</ul>

<h2>Remaining Product Backlog</h2>
<p>The product backlog was completed as a by-product of completing our sprint user stories.</p>

<h2>File Structure</h2>
<p>The end user version of the project builds an executable containing all the code. In addition, the project also extracts the required SFML dlls and a resource folder into the source folder of the executable. The resource folder contains fonts, images, and a CSV containing the board's data.</p>

<p>The developer version of the project is a Visual Studio solution. The required headers and source files are all in the same folder as the Visual Studio solution. There are additional SFML dlls for both release and debug builds included in the solution directory. 
In addition, there is another subfolder containing SFML's lib files and include headers.</p>

<h2>Future Contributions</h2>
<p>Team members can contribute to the project through the project GitHub. The keeper of the project will be Zachary McBride. New people can become contributers by cloning the master branch and sending merge requests. As a baseline, they will need to understand basic Object-Oriented programming and SFML features to contribute.</p>
