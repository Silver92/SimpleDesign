#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Light {
public:
	void on() {
		cout << "Light on" << endl;
	}
	void off() {
		cout << "Light off" << endl;
	}
};

class Stereo{
public:
	void on() {
		cout << "stereo on" << endl;
	}
	void setCD() {
		cout << "stereo off" << endl;
	}
	void setVolume() {
		cout << "stereo set volume" << endl;
	}
};

//=============================================================

class Command{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

// Use this class to initialize the command, thus 
// we don't have to add if statements to see if there
// is commands in the controller
class NoCommand: public Command{
public:
	void execute() {
		cout << "No command" << endl;
	}
	void undo() {}
};

class LightOnCommand: public Command {
public:
	Light* light;
	LightOnCommand(Light* light) {
		this->light = light;
	}

	void execute() {
		light->on();
	}

	void undo() {
		light->off();
	}
};

class LightOffCommand: public Command {
public:
	Light* light;
	LightOffCommand(Light* light) {
		this->light = light;
	}

	void execute() {
		light->off();
	}

	void undo() {
		light->on();
	}
};

class StereoOnWithCDCommand: public Command {
public:
	Stereo* stereo;
	StereoOnWithCDCommand(Stereo* stereo) {
		this->stereo = stereo;
	}

	void execute() {
		stereo->on();
		stereo->setCD();
		stereo->setVolume();
	}

	void undo() {

	}

};


//=============================================================
class SimpleRemoteControl {
	Command* slot;
public:
	 SimpleRemoteControl() {}
	 void setCommand(Command* command) {
	 	slot = command;
	 }
	 void buttonWasPressed() {
	 	slot->execute();
	 }

};

class RemoteControl {
	Command* onCommands[7];
	Command* offCommands[7];
	Command* undoCommand;

public:
	RemoteControl() {
		for(int i=0; i<7; i++) {
			onCommands[i] = new NoCommand();
			offCommands[i] = new NoCommand();
		}
		undoCommand = new NoCommand();
	}

	void setCommand(int slot, Command* onCommand, Command* offCommand) {
		onCommands[slot] = onCommand;
		offCommands[slot] = offCommand;
	}

	void onBottonWasPushed(int slot) {
		onCommands[slot]->execute();
		undoCommand = onCommands[slot];
	}

	void offButtonWasPushed(int slot) {
		offCommands[slot]->execute();
		undoCommand = offCommands[slot];
	}

	void undoBottonWasPushed() {
		undoCommand->undo();
	}
};

void Test01 () {
	RemoteControl* remoteControl = new RemoteControl();

	Light* light = new Light();
	Stereo* stereo = new Stereo();

	LightOnCommand* lightOn = new LightOnCommand(light);
	LightOffCommand* lightOff = new LightOffCommand(light);
	StereoOnWithCDCommand* stereoOn = new StereoOnWithCDCommand(stereo);

	remoteControl->setCommand(0, lightOn, lightOff);

	remoteControl->onBottonWasPushed(0);
	remoteControl->undoBottonWasPushed();
}


int main() {
	Test01();

	return 0;

}