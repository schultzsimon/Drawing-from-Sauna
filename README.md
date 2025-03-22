Drawing from Sauna
BA New Media Composition graduation piece

"Drawing from Sauna" is a performance art piece that integrates Internet of Things (IoT) technology to create a seamless performance experience with hidden electronics.



Technical Implementation
This project uses hidden electronics to control sound and visuals during a performance, without any visible technology disrupting the aesthetic experience.
Hardware Components
The system consists of four main components:



Matchbox Sender (M5StickC PLUS)

Hidden inside the matchbox used to light a candle at the beginning of performance
Features a button that triggers the performance sequence
When pressed, it triggers a match strike sample and after 15 seconds fades in the neural network audio decoder


Towel Sender (M5StickC PLUS)

Placed against the performer's spine within the fold of a towel
Contains a 6-axis Inertial Measurement Unit (IMU)
Sends motion data that is highly sensitive - small movements make big sonic changes
The motion data navigates a neural network's latent space of sound recordings


Bench Sender (LILYGO TTGO T7 Mini32 ESP32)

Hidden underneath the bench with a battery pack
Connected to two pressure sensors on the bench's sitting surface
As the performer shifts weight, various musical parameters are controlled
Controls levels between outputs, effect amounts, playback speed, and more
The parameter mapping changes throughout the performance


Receiver (M5StickC PLUS)

Connected to an off-stage laptop running Max/MSP
Receives data from all three sender units
Translates incoming data into Open Sound Control (OSC) messages
The OSC messages are scaled and assigned to various tasks in a custom Max patch



Communication Technology

All devices communicate using the ESPNOW wireless protocol
No visible electronics are present on stage, maintaining the aesthetic integrity of the performance
The system enables subtle physical movements to create significant sonic changes

Code Structure
The repository contains Arduino code (.ino files) for each of the four components:

MATCHBOX.ino: Code for the M5StickC PLUS hidden in the matchbox
TOWEL.ino: Code for the M5StickC PLUS attached to the performer
BENCH.ino: Code for the LILYGO TTGO T7 Mini32 ESP32 under the bench
RECEIVER.ino: Code for the M5StickC PLUS that receives data and interfaces with Max

Performance Flow

The performer uses the matchbox to light a candle
A thumb press on the matchbox triggers the sound of a match strike
After 15 seconds, the main sound begins to fade in
Throughout the performance, the motion of the performer (captured by the Towel sender) navigates the neural network's sound space
Weight shifting on the bench controls various audio parameters

Technical Requirements

M5StickC PLUS (3 units)
LILYGO TTGO T7 Mini32 ESP32 (1 unit)
Pressure sensors (2 units)
Battery packs
Computer running Max
