# HTMLParser
A simple, easy to use HTML parser written in C++ with functionality similar to JSoup.

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
