<?xml version="1.0" encoding="ISO-8859-15"?>
<xsl:stylesheet version="1.0"
				xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output encoding="ISO-8859-15"/>
  
  <xsl:template match="br">
	<br/>
  </xsl:template>
  
  <xsl:template match="a">
	<a href="{@href}"><xsl:apply-templates/></a>
  </xsl:template>
  
  <xsl:template match="main">
	<html>
	  <head>
		
		<title>codeare 1</title>
		
		<meta http-equiv="content-type" content="text/html; charset=utf-8"/>
		<meta http-equiv="content-language" content="en" />
		
		<meta name="description" lang="en" content="" />
		<meta name="keywords" content="MRI, image reconstruction, image
									   reconstruction library, codeare, MRI, Compressed sensing,
									   non-cartesian, SENSE, kt-Points, variable density spiral, k-space
									   trajectory, GRAPPA, parallel imaging, selective excitation, open-source" /> 
		
		<link rel="stylesheet" href="screen.css" type="text/css" media="screen" />
		<link rel="stylesheet" href="codeare.css" type="text/css" media="screen" />
				
		<script type="text/javascript" src="sh_main.js"></script>
		<script type="text/javascript" src="sh_cpp.js"></script>
		<script type="text/javascript" src="sh_xml.js"></script>
		<script type="text/javascript" src="sh_sh.js"></script>
		
		<link type="text/css" rel="stylesheet" href="sh_style.css"/>

	  </head>
	  <body onload="sh_highlightDocument();">
		
		<div id="topborder"></div>
		
		<div id="sidebar">
		  <h1><a href="http://codeare.org/">codeare<em>1.0b</em></a></h1>
		  
		  <ul id="nav">
			<li><a href="index.html">home</a></li>
			<li><a href="download.html">download</a></li>
			<li><a href="install.html">install</a></li>
			<li><a href="gettingstarted.html">getting started</a></li>
			<li><a href="developerguide.html">developer guide</a></li>
			<li><a href="api/html/index.html" target="_api">api annotation</a></li>
			<li><a href="contact.html">contact</a></li>
		  </ul>
		  <div class="callout">
			<a href="download.html" >v1.0b released<br />
			<span class="date">on 23 mar 2012</span><br/>by kaveh vahedipour</a>
		  </div>
		  <br/>

		</div>
		
		<div id="content">

		  <xsl:value-of select="article" disable-output-escaping="yes"/>
		  
		</div>
		
		<div id="rightbar">
		  <div class="callout">
			<h1>visit also</h1> <br/>
			<a href="http://www.jemris.org" target="_jemris">jemris
			mri simulator</a> 
			<br/>
			open-source full-featured parallel tx/rx mri sequence and
			hardware simulator.
			<br/><br/> 
			<a href="http://www.drcmr.dk/bloch" target="_hansen">bloch
			  simulator for education in mri and nmr</a> 
			<br/>
			free educational mri and nmr sofware. multi- os/platform 
			without installation of software. remarkable and
			beautiful effort by lars hanson from drcmr, hvidovre, dk.
			<br/><br/> 
			<a href="http://gadgetron.sourceforge.net"
			   target="_mriunbound">gagdetron</a>
			<br/>
			a comparable project to codeare by <em>michael hansen</em> and
			<em>thomas s�rensen</em>.
			<br/><br/> 
			<a href="http://www.ismrm.org/mri_unbound/"
			   target="_mriunbound"> mri unbound</a>
			<br/>
			a collaborative forum for mri data acquisition and image
			reconstruction maintained by the unbreakable <em>jim pipe</em>. 

		  </div>
		</div>
		
	  </body>
	</html>
  </xsl:template>
</xsl:stylesheet>
    
