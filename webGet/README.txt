./webGet 
usage: webGet (version: 1.001   ) :  a simple URL GET client 
usage:	./webGet URL iterations delay debugFlag
usage:	URL: full URL decription
usage:	delay: in seconds
usage:	debugFlag:  0: none; 1:some; 2:data
usage:	Example:  ./webGet http://darkhelmet.cs.clemson.edu/DataFile2.dat 1 1 0




Modified 11-14-2011
------------------------------

1. Building
-----------
Extract from gzipped tarball (e.g. "tar xzf hw3q3.tar.gz") and do "make".  Run the resulting "webGet" executable.

Run ./makeDataFiles.script. This calls the program createDataFiles (params fileSize and fileID) six times to create the data files
DataFile1.dat - DataFile6.dat.  Which range in size from 100 to 10Mbytes.

To rebuild, issue 'make clean' and then 'make'


2. Running
----------
Run with no arguments for a quick usage summary.

The "URL" argument must be a fully qualified HTTP URL.  It must begin with "http://" (sorry, no SSL support) and must contain a complete path (i.e. "http://foo/" is incomplete; needs to be "http://foo/bar").  Alternative port numbers are accepted (e.g. "http://foo:8080/bar" opens a socket on port 8080) but not required; webGet will default to port 80.

The "iterations" argument must be a valid integer.  If iterations is greater than 0, webGet will download the URL <iterations> times.  Otherwise, webGet will run forever.  ("iterations" cannot be negative.)

The "delay" argument must be a valid, non-negative decimal (floating-point) number.  webGet will sleep for <delay> seconds between each request/transaction.  Specifying "0" for both iterations and delay is a good way to get in trouble...

The "debugFlag" argument must be a valid integer.  If debugFlag is non-zero (i.e. "true"), then webGet will dump some real-time statistics to stdout on each iteration.  Otherwise, webGet will not print anything until it terminates.

3. Data
-------
webGet prints out a summary on termination (whether that comes by reaching <iterations> iterations [assuming <iterations> is non-zero] or by the user interrupting the program with ^C).  Included are the following fields:

  * Start time (via ctime())
  * End time (via ctime())
  * Seconds elapsed (floating-point; to microsecond precision)
  * Iterations (actually run--not the "iterations" argument)
  * Total bytes sent and received
  * Average throughput (bytes received / response time; in bytes-per-second)
  * Averate response time (in seconds)



