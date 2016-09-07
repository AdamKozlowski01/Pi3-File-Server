Pi File Client (PiFi)

Client Run:
	load any relevant settings
	read any command line arguments
	set up Crypto-object
		Set up Deffie-Heidman-Exchange-object
	set up Thread-Pool object

	Client opens connection to the server on port X

	Server and Client set up Key-Exchange and AES key which they will use to talk on for the remainder of the session

	Server asks for credentials

	Loop through the following until the server sends "login successful":

		Client sends first a plain-text string (set whole thing toUpper()			(format? UTF-8 for easy Java integration? (Can make that it's own 
																					connection type for later, which means we 
																					may need an abstract connection factory on the server for 
																					different connection types)

	
		If Client sends "create account" then the server will prompt to create credentials:
			Client then sends a new plaintext string using the format dictated by the connection-object
			Client takes the user's input password (10 characters long, two non-adjacent captial letters, a number, and a symbol (use a seprate thread 
			to check for each one, aka 4 threads))
			Client asks for user's email in case they ever need a new email.

			Server responds with account created successfully.
			GO TO TOP OF LOOP

		If Client sends anything else, it will send a second string shortly after which is the password.

		Server replies with either invalid credentials or login successful.

	Loop the following until user asks to exit:
		Print the names of all folders and files in the user's folder.

		read user input for the following:

		<Command> <Target> <Options>

		1.) "PULL" the name of a file/file/path
			-> Recieve the AES Key for the file
			-> Decrypt the file using multiple threads to solve different chunks
			-> Put the file together and save it in the user's set path
			-> For folders repeat these steps for every file in the folder, including other folders

			options:
				-p $path (Pull to a file path that's different from the config one)
				

		2.) "OPEN" the name of a folder/file/path
			-> print the contents of the folder to the user
			-> prints the file info contents to the user

		3.) "PUSH" the name of a file/folder/path
			-> Send the file to the server
				-> Send the file name
				-> Send the file type
				-> Send the file in chunks

		4.) "SHARE" username | ""
			-> if valid username entered, put a shortcut link of the file in that user's folder and add a new entry to the database for that user
			-> print a list of all users shared with and the names and paths of all files shared with that user

		5.) "EXIT"
			-> Close the connection and leave the loop


