# myLibrary
Some useful codes, such as linklist, LRU replacement...

## How to use?
### Environment set

I used **Ubuntu 14.04** operating system to implement.

You can use **docker** to build your environment by following the steps below.

	cd /myLibrary
	docker build -t mylibrary .
	
When you done these steps, you can use `docker images ` command to check the new images named **mylibrary**.

Then you can follow the rest of steps to run those programs in Ubuntu14.04 environment.

	docker run --name myLibrary -it mylibrary bash	
		 


 
