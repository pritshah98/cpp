Run server with following commands:

./server <IP_Address> <Port #>
-------------------------------------
ex: ./server 127.0.0.1 13000

Run Client with following commands:

	- To upload a message to server:
		./client <IP_Address> <Port #> <-u> <Message>
	ex. ./client 127.0.0.1 13000 -u "Hello, World."
**Message must be from 0-150 characters

	- To download a message from server:
		./client <IP_Address> <Port #> <-d>
	ex. ./client 127.0.0.1 13000 -d
