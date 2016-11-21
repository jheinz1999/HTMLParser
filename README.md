# HTMLParser
A simple, easy to use HTML parser written in C++ with functionality similar to JSoup.

Installation:
--------------

There is no platform-dependent code in this project. It will compile on any system that can run g++. It has been tested with g++ 4.9.3 under linux, as well as g++ 6.1.0 using MinGW on Windows 7. To compile, type

'make'

How to use:
-----------

In its current stage, this program will only analyze your HTML file. It will print out a list of the tags in the order that they appear, and will indent them to exhibit its parent/child tags. In addition, the program will print out how many of each tag are in the HTML file. This program is in a pre-alpha stage, and its functionality is extremely limited. 

Latest update: 11/21/16
------------------------

- Refined tag organization algorithm; HTMLParser now puts tags in the right place

Known Bugs:
------------

- The program will crash if two similarly-nested tags exist.

Example of an error-causing HTML file:

<html>

	<head>
		<title></title>
		<meta></meta>
	</head>

	<body>
		<h1>Welcome to old navy</h1>
		<p><b>Here we have chicken</b></p>
		<p><b><i>COME TO OLD NAVY TODAY</i></b></p>
		
	</body>

</html>

The program will work if you take out the i tag. I am currently working to fix this issue.
