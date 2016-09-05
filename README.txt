The Pi3 File Server is a multi-client server which aims to create end-to-end encrypted file storage and transfer.

The Server has the following goals:
	1.) All data on the server is encrypted and unreadable by server operators or unautherized clients.

	2.) Clients can transfer files from the server to their devices

	3.) Clients determine the privacy of their files, and can choose who to share files with

SERVER SYSTEMS AND SUB-SYSTEMS

	Server - The abstraction of a Server, starts and shutsdown the server.

	Connection_Handler - Handles incoming connections, manages the queue of connection, requests threads for each connection, and creates Connection objects.
		Connection_Factory - Creates new connection objects
			Connection - The abstraction of a connection

	Thread_Pool - Manages the allocation and release of threads, updates other systems when threads become available.

	Crypto - Manages the encryption/decrpytion of data, key exchanges, etc.
		Key_Exchange - Manages the key-exchange protocols

	Verification - Verifies user credentials (Using Database)

	Streaming - Handles the transfer of files to and from the server (Using Database)

	Database - Handles the search, updating, and return of user and file data
		User - The abstraction of a user
		File - The abstraction of a file

The Server runs as follows:
	Boot Up:
		Server generates it's Server Key (For the encryption of file keys)
		Server sets up it's Connection-Handler System
		Server sets up it's Thread-Pool System
		Server sets up it's Crypto-System
			Server sets up it's Key-Exchange System
		Server sets up it's Verification-System
		Server sets up it's Streaming System
		Server sets up it's Database System

	Listening:
		Server listens on it's port
		Connection-Handler gets a request and puts it in the queue
			Connection-Handler asks the Thread-Pool for a thread to handle the connection.  When threads are available the Thread-Pool will ask all systems which use it if they need threads, prioritizing Connection-Handling.
		The Thread handed from the Thread-Pool system creates an instance of a Connection object.
			Connection object sends a message prompting for client credentials
			The Connection waits for a response, and passes it to the Verifier.
				The verifier checks to see if the credentials match with a client in the Database.
					IF YES:
						The verifier tells the Connection Object that this a legit client.
						The Connection Object returns to the client a list of readable files in their folder (and shortcuts to files shared with them)
						IF USER ADDS A FILE:
							If the user wants to add a file, set up a Key-Exchange between client and server.
							Once keys are set, the client FTPs the file over to the Server.
							The Server stores the file in the user's Folder leaving it encrypted.
							Encypt the file's decryption key using the Server Key and store it in the Database with the new file entry.
						IF USER WANTS TO STREAM A FILE:
							Client selects a file to stream.
							Create a Key-Exchange between the Client and the Server.
							Decrypt a copy of the file key (using the Server Key) and encrypt using the new Client-Server key.
							Send the encrypted Client-Server key.
							Confirm that the Client recieved the key.
							Copy bits and send them down the wire.
						IF USER WANTS TO DELETE A FILE:
							Find the file in the Database and all Database copies of it.
							FOR EACH FILE RETURNED:
								Lose the pointer to the file.
								0 out the encypted key in the Database
								Delete the Database enrty.
						IF USER WANTS TO SHARE A FILE WITH ANOTHER USER:
							Check with the Database that the other user exists.
							Create a shortcut to the file in the User's Folder
							Add a new File entry in the Database that is a copy except with the other user's ID instead of the original uploader.
						IF USER DISCONNECTS:
							Close the connection
							return the thread to pool.

					IF NO:
						Close the connection object, return the thread to pool.
					IF NEW USER:
						Prompt the client for the credentials they want to have
						Save the credentials in the Database
						Create a Folder for the user

