<?xml version="1.0"?>
<!-- 
	Manifest XSLT style sheet version 1.00.00.00 
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="html"/>

<xsl:preserve-space elements=""/>

<xsl:template match="manifest">
	<html>
    <head>
     	<style type="text/css" media="screen">
				body {
					font-family: Verdana, Microsoft Sans Serif, Arial Black;
					color: black;
					padding: 0;
					margin: 0;
					font-size: 12px;
					line-height: 18px;
					background-color: white;
				}

				img {
					border: 0;
				}
				
        h1 {
					font-size: 20px;
					color: rgb(56,56,56);
				}

				h2 {
					font-size: 16px;
					color: rgb(0,0,0); 
				}

				h3 {
					font-size: 10px;
					color: rgb(122,122,122);
				}

				#container { 
					position: relative;
					width: 800px;
					height: auto;
					margin: 0;
					padding: 0;
					background-color: white;
				}

				#heading {
				    position: relative;
					height: auto;
				 	margin: 0;
				 	margin-left: 20px;
				 	padding: 0;
				 	padding-top: 10px;
					color: rgb(56,56,56);
				}

				#content {
					position: relative;
					width: 760px;
					height: 300px;
					border-style: inset;
					border-width: 1px;
					border-color: rgb(219,219,219);
					margin: 10px;
				 	padding: 5px;
				 	background-color: white;
				 	overflow: auto;
				}

				#footer {
				    position: relative;
				    width: 800px;
				    float: left;
				    margin: 0;
				    margin-top: 25px;
				 	padding: 0;
				 	text-align: center;
				    color: rgb(210,210,210);
				}

				#TOC {
					margin: 0;
					margin-top: 20px;
					padding: 0;
				}

				#TOC ol {
					list-style-type: upper-roman;
				}

				#TOC ol li a {
					color: black;
					display: block;
					padding: 2px 0;
					text-decoration: none;
				}

				#manifest {
					margin: 0;
					margin-top: 20px;
					padding: 0;
				}

				#ECCN {
					margin: 0;
					margin-top: 20px;
					padding: 0;
				}

				#legend {
					margin: 0;
					margin-top: 20px;
					padding: 0;
				}

				#credits {
					margin: 0;
					margin-top: 20px;
					padding: 0;
				}

				#disclaimers {
					margin: 0;
					margin-top: 20px;
					padding: 0;
				}

				#license {
					margin: 0;
					margin-top: 20px;
					padding: 0;
				}

				.mtable {
				 	padding: 2px;
				 	width: 100%;
				}

				.mtable td {
					text-align: left;
					vertical-align: top;
					border: 1px solid black;
					padding: 5px;
					font-size: 12px;
				}
		  </style>
      
      <title>
       	<xsl:value-of select="product/name"/>
      </title>
    </head>
    
    <body>
    	<div id="container">

			  <div id="heading">
				  <h1> Manifest for <xsl:value-of select="product/name"/> 
               Version <xsl:value-of select="product/version"/> 
          </h1>
				  <p> <xsl:value-of select="product/description"/> </p>
			  </div>

        <div id="content"> 
          <div id="TOC">
	          <h2> Table of Contents </h2>
		        <ol>
			        <li><a href="#legend"> Manifest Legend</a></li>
			        <li><a href="#disclaimers"> Disclaimers</a></li>
			        <li><a href="#export"> Export Information</a></li>
			        <li><a href="#manifest"> Manifest</a></li>
			        <li><a href="#credits"> Credits and Attributions</a></li>
			        <li><a href="#license"> License Text </a></li>
		        </ol>
	        </div>
	          
	        <div id="legend">
		        <a name="legend"><h2>Legend (explanation of the fields in the Manifest Table below)</h2></a>
		        <table class="mtable">
		    	    <tr>
		    		    <td>Software Name</td> 
		    		    <td>The name of the application or file</td>
		    	    </tr>
		    	    <tr>
		    		    <td>Version</td> 
		    		    <td>Version of the application or file</td> 
		    	    </tr>
		    	    <tr>
		    		    <td>License Type</td> 
		    		    <td>Type of license(s) under which TI will be providing software to 
                    the licensee (e.g. BSD, GPLv2, TI TSPA License, TI Proprietary 
                    License). See Open Source Reference License Disclaimer in the 
                    Disclaimers Section.</td> 
		    	    </tr>
		  	  	  <tr>
		    		    <td>Location</td> 
		    		    <td>The directory name and path on the media (or in an archive) where 
                    the Software is located.</td>
		    	    </tr>	      		
		    	    <tr>
		    		    <td>Delivered As</td> 
		    		    <td>This field will either be "Source", "Binary" or "Source and Binary" 
                    and is the form the content of the Software is delivered in.  If the 
                    Software is delivered in an archive format, this field applies to 
                    the contents of the archive. If the word Limited is used with Source, 
                    as in "Limited Source" or "Limited Source and Binary" then only 
                    portions of the Source for the application are provided.</td> 
		    	    </tr>
		    	    <tr>
		    		    <td>Modified by TI</td> 
		    		    <td>This field will either be "Yes" or "No". A "Yes" means TI has made 
                    changes to the Software. A "No" means TI has not made any changes. 
                    Note: This field is not applicable for Software "Obtained from" TI.</td>
		    	    </tr>
		    	    <tr>
		    		    <td>Obtained from</td> 
		    		    <td>This field specifies from where or from whom TI obtained the Software. 
                    It may be a URL to an Open Source site, a 3rd party licensor, or TI 
                    (if TI developed the software). If this field contains a link to Open 
                    Source software, the date TI downloaded the Software is also recorded. 
                    See Links Disclaimer in the Disclaimers Section.</td> 
		    	    </tr>
		        </table>	      	
	        </div>
	      	    
	        <div id="disclaimers">
	          <a name="disclaimers"><h2>Disclaimers</h2></a>
				    
            <p><u>Export Control Classification Number (ECCN)</u></p>
				    <p>Any use of ECCNs listed in the Manifest is at the user's risk and without 
               recourse to TI.   Your company, as the exporter of record, is responsible 
               for determining the correct classification of any item at the time of export. 
               Any export classification by TI of Software is for TI's internal use only 
               and shall not be construed as a representation or warranty regarding the 
               proper export classification for such Software or whether an export license 
               or other documentation is required for exporting such Software.</p>	
				    
            <p><u>Links in the Manifest</u></p>
				    <p>Any links appearing on this Manifest (for example in the "Obtained from" 
               field) were verified at the time the Manifest was created. TI makes no 
               guarantee that any listed links will remain active in the future.</p>	
				    
            <p><u>Open Source License References</u></p>
				    <p>Your company is responsible for confirming the applicable license terms for 
               any open source Software listed in this Manifest that was not "Obtained from" 
               TI.  Any open source license specified in this Manifest for Software that 
               was not "Obtained from" TI is for TI's internal use only and shall not be 
               construed as a representation or warranty regarding the proper open source 
               license terms for such Software.</p>	
	      		
            <xsl:apply-templates select="disclaimer"/>
	        </div>
	      	    
          <div id="ECCN"> 
            <a name="export"><h2> Export Information </h2></a>
				    <p> ECCN for Software included in this release:  <xsl:value-of select="product/eccn_software"/> </p>
				    <p> ECCN for Technology (e.g., user documentation, specifications) included in this release:  <xsl:value-of select="product/eccn_technology"/> </p>
          </div>
	          
	        <div id="manifest">
		        <a name="legend"><h2> Manifest </h2></a>
		        <p> See Legend above for a description of the columns and possible values.</p>
		        <table class="mtable">
		          <tr>
		    	      <td bgcolor="#DCDCDC"><b>Software Name</b></td>
		    	      <td bgcolor="#DCDCDC"><b>Version</b></td>
		    	      <td bgcolor="#DCDCDC"><b>License Type</b></td>
		    	      <td bgcolor="#DCDCDC"><b>Delivered As</b></td>
		    	      <td bgcolor="#DCDCDC"><b>Modified by TI</b></td>
		    	      <td bgcolor="#DCDCDC" colspan="2">&#160;</td>
		          </tr>
  				    <xsl:apply-templates select="package"/>
				    </table>    	
	        </div>
	      	    
	        <div id="credits">
	    	    <a name="credits"><h2>Credits</h2></a>
	    	    <xsl:apply-templates select="credit"/>
	        </div>

	        <div id="license">
	    	    <a name="license"><h2>Licenses</h2></a>
	    	    <xsl:apply-templates select="ltext"/>
	        </div>
	      	    
        </div>	  

			  <br/>

			  <div id="footer">
				  <h3><a href="http://www.ti.com">www.ti.com</a></h3>
			  </div>

		  </div>

	  </body>

  </html>
</xsl:template>

<xsl:template match="package">
  <tr><xsl:apply-templates/></tr>
</xsl:template>

<xsl:template match="name">
  <td rowspan="2"><xsl:apply-templates/></td>
</xsl:template>

<xsl:template match="version">
  <td rowspan="2"><xsl:apply-templates/></td>
</xsl:template>

<xsl:template match="license">
  <td rowspan="2"><xsl:apply-templates/></td>
</xsl:template>

<xsl:template match="format">
  <td rowspan="2"><xsl:apply-templates/></td>
</xsl:template>

<xsl:template match="modified">
  <td rowspan="2"><xsl:apply-templates/></td>
</xsl:template>

<xsl:template match="location">
  <td><b>Location</b></td> 
  <td><xsl:apply-templates/></td>
</xsl:template>

<xsl:template match="obtainedfrom">
  <tr>
    <td><b>Obtained from</b></td> 
    <td><xsl:apply-templates/></td>
  </tr>
</xsl:template>

<xsl:template match="obtainedfrom[@url]">
  <tr>
    <td><b>Obtained from</b></td> 
    <td><a href="{@url}"><xsl:apply-templates/></a></td>
  </tr>
</xsl:template>

<!-- Empty Product template to filter out the block since we pulled the specific fields above -->
<xsl:template match="product">
</xsl:template>

<xsl:template match="credit/title">
	<p><u><xsl:apply-templates/></u></p>
</xsl:template>

<xsl:template match="credit/text">
	<p><xsl:apply-templates/></p>
</xsl:template>

<xsl:template match="disclaimer/title">
	<p><u><xsl:apply-templates/></u></p>
</xsl:template>

<xsl:template match="disclaimer/text">
	<p><xsl:value-of select="." disable-output-escaping="yes" /></p>
</xsl:template>

<xsl:template match="link[@url]">
   <td><a href="{@url}"><xsl:apply-templates/></a></td>
</xsl:template>

<xsl:template match="ltext">
  <p><xsl:value-of select="." disable-output-escaping="yes" /></p>
</xsl:template>


<!-- Empty Private template to filter out the block (ie not display it) -->
<xsl:template match="private">
</xsl:template>

</xsl:stylesheet>