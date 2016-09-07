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

class ConnectionFactory{

private:
protected:
public:
	virtual Connection* createConnection(int fileDescrptr) = 0;

};

class ConnectionFactory_v1{

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