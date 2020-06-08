# OSUClue
<h1>Overview</h1>
<p>This project is a desktop reproduction of the classic board game Clue! The goal of the project is to create a high-fidelity GUI implementation with multi-player capability.</p>

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

<p>The server needs to enable port forwarding first. The following link will show how to do it.</p>

<p>https://www.noip.com/support/knowledgebase/general-port-forwarding-guide/</p>

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
Final State/condition of the software

<h2>Known Issues/Bugs</h2>
<ul>
<li>The installer may be flagged as an untrusted source.</li>
<li>The game may need to be run as an admin.</li>
</ul>

<h2>Remaining Product Backlog</h2>
<ul>
<li>As a social distancer, I want to be able to connect to a server to play this game with my friends.</li>
<li>As a person who doesn't do well without a clearly-designed UI, I want the game functinality to be hidden and driven by the UI.</li>
<li>As someone who likes things to be uncomplicated, I want to be presented with a list of possible actions that can be taken when it is my turn based on my token's location.</li>
<li>As a fan of secrecy, I want to be able to disprove a suggestion by only showing the player who made the suggestion my card.</li>
<li>As a fan of deception, I want to be able to make a suggestion using my own cards so that I can trick other players into thinking they might be in the solution.</li>
<li>As a person who likes fairness, I want a player who makes a wrong Accusation to be turned into an observer whose sole purpose is to provide information when Suggestions are made.</li>
<li>As a fan of sabotage, I want to be able to block an opponent in a room by standing in the space in front of the door.</li>
<li>As a fan of doors, I want the doors in Clue to be in the right place and functioning correctly so that Players can only enter and exit a room through them.</li>
<li>As someone who likes rules, I want to make sure that the player playing Miss Scarlet goes first and then the player to their left, etc. in accordance with the rules.</li>
<li>As someone who gets easily distracted, I want there to be some sort of log of what the other players have done so that I can stay in the loop.</li>
<li>As someone else who relies on the notebook feature, I would like it to be accessible at all times so I can plan my moves.</li>
<li>As someone who likes to play as a particular character, I would like to be able to choose who I play and not allow anyone else to be the same character as me.</li>
<li>As a stickler for rules, I want it to be impossible for two tokens to be on the same space (unless they're in a room together).</li>
<li>As a fan of secret passages, I want the secret passages in the computer game to be implemented just like in the board game.</li>
<li>As someone who is consistently frustrated when the other players move my token when making a suggestion or accusation, I would like this version of Clue to emulate that frustration by automatically moving my token when a suggestion is made involving my character.</li>
<li>As a Clue purist, I would like there to be uniform consistency in naming conventions across the game.</li>
<li>I'm not sure if we want for character token classes to drive placement on the board, or the board class contains the character class.</li>
<li>As someone who doesn't have a high performance computer, I want to be able to run this game so I can play with my friends.</li>
<li>As someone who struggles with seeing things on my screen, I would like tokens to be easily distinguishable from the board itself, so that I can play the game effectively.</li>
<li>As a player, I want to be able to play Clue with up to 6 people so that I can play with all my friends.</li>
</ul>

<h2>File Structure</h2>
<p>The end user version of the project builds an executable containing all the code. In addition, the project also extracts the required SFML dlls and a resource folder into the source folder of the executable. The resource folder contains fonts, images, and a CSV containing the board's data.</p>

<p>The developer user of the project is a Visual Studio solution. The required headers and source files are all in the same folder as the Visual Studio solution. There are additional SFML dlls for both release and debug builds included in the solution directory. 
In addition, there is another subfolder containing SFML's lib files and include headers.</p>

<h2>Future Contributions</h2>
<p>Team members can contribute to the project through the project GitHub. The keeper of the project will be Zachary McBride. New people can become contributers by cloning the master branch and sending merge requests. As a baseline, they will need to understand basic Object-Oriented programming and SFML features to contribute.</p>
