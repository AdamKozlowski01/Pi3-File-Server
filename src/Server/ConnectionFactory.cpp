/*********************************************
* ConnectionFactory.cpp
* Created By: Adam Kozlowski
* Last Updated: 8/6/2016
* Factory for creating different kinds of connections
*
*
*********************************************/

class Connection{
private:
protected:
public:
	virtual void connectionProtocol() = 0;

};

class StandardConnection : public Connection{
private:
	int connection_fd;

protected:
public:
	Connection(int fileDescrptr){}
	~Connection(){}
	void connectionProtocol(){
		//set up key exchange for the session
		
		//ask for credentials

		//check credentials or if create account mode, ask to create credentials

		//send names of all folders in user's file
		//process requests until connection time out or ends
		
	}
};

class ConnectionFactory{

private:
protected:
public:
	virtual Connection* createConnection(int fileDescrptr) = 0;

};

class ConnectionFactory_v1 : public ConnectionFactory{

private:
protected:
public:
	ConnectionFactory(){}
	~ConnectionFactory(){}
	Connection* createConnection(int fileDescrptr){
		//creates a connection object
		//returns the connection info to the main thread
	}


};