<?xml version='1.0' encoding="iso-8859-1"?>
<!--
 - Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
 -
 - Permission to use, copy, modify, and/or distribute this software for any
 - purpose with or without fee is hereby granted, provided that the above
 - copyright notice and this permission notice appear in all copies.
 -
 - THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 - REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 - AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 - INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 - LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 - OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 - PERFORMANCE OF THIS SOFTWARE.
-->

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:xi="http://www.w3.org/2001/XInclude"
  xmlns:db="http://docbook.org/ns/docbook">

  <!-- <optional> and <command> rendered in <programlisting>s.
       For each overriden element, the parameters must be defined.
       They are mandatory, and $probe must be set to 0 by default.

       Only dblatex 0.2.12, with the verbatim.boldseq template works
       here.
       -->
  <xsl:template match="optional|command" mode="latex.programlisting">
    <xsl:param name="co-tagin" select="'&lt;:'"/>
    <xsl:param name="rnode" select="/"/>
    <xsl:param name="probe" select="0"/>

    <xsl:call-template name="verbatim.boldseq">
      <xsl:with-param name="co-tagin" select="$co-tagin"/>
      <xsl:with-param name="rnode" select="$rnode"/>
      <xsl:with-param name="probe" select="$probe"/>
    </xsl:call-template>
  </xsl:template>

  <!-- skip over docinfo section when including man pages in ARM -->
  <xsl:template match="docinfo"/>

  <!-- Skip abstracts and sidebars -->
  <xsl:template match="abstract"/>
  <xsl:template match="sidebar"/>

  <!-- Two section level in the Table of contents -->
  <xsl:param name="toc.section.depth">2</xsl:param>

  <!-- Do not show the collaborators listed in bookinfo -->
  <xsl:param name="doc.collab.show" select="0"/>

  <!-- No revision history in the front matter -->
  <xsl:param name="latex.output.revhistory" select="0"/>

  <!-- Do not put sections for appendixes in TOC (set tocdepth=0) -->
  <!-- Do not put appendixes in TOC (set tocdepth=-1) -->
  <xsl:template match="appendix">
    <xsl:if test="not (preceding-sibling::appendix)">
      <xsl:call-template name="set-tocdepth">
  <!-- -1 for not appendix -->
  <!-- 0 for no sections from appendix -->
        <xsl:with-param name="depth" select="0"/>
      </xsl:call-template>
    </xsl:if>
    <xsl:apply-imports/>
  </xsl:template>

  <!-- Use the book class layout (instead of report) -->
  <xsl:param name="latex.class.book">book</xsl:param>

  <!-- Printable version -->
  <!-- the blue boxes won't show up in print, but change to black and the boxes
  disappeared -->
  <!-- urlcolor=black is for email addresses etc -->
  <!-- this is for a black-and-white PDF, no hyperlinks or URL colors -->
  <!-- xsl:param name="latex.class.options">nohyperlink,colorlinks,linkcolor=black,urlcolor=black</xsl:param> -->

  <!-- Variable list terms on line by themselves -->
  <xsl:param name="term.breakline">1</xsl:param>

  <!-- preface heading in TOC, 2 to get sections also -->
  <xsl:param name="preface.tocdepth">2</xsl:param>

  <!-- set latex secnumdepth, choose level of subsections to number -->
  <xsl:param name="doc.section.depth">1</xsl:param>

  <xsl:template name="inline.sansserifseq">
    <xsl:param name="content">
      <xsl:apply-templates/>
    </xsl:param>
    <xsl:text>\textsf{</xsl:text>
    <xsl:copy-of select="$content"/>
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template match="othercredit|othername"/>

  <!-- 21/Oct/2009 reed - don't widen tables -->
  <xsl:param name="newtbl.autowidth">default</xsl:param>

  <!-- 2014-09-25 reed - use Q and A instead of number -->
  <xsl:param name="qanda.defaultlabel">qanda</xsl:param>

  <!-- 2014-10-07 reed - add index to table of contents -->
  <xsl:param name="index.tocdepth">5</xsl:param>
  <xsl:param name="index.numbered">0</xsl:param>

  <!-- Include our copyright generator -->
  <xsl:include href="copyright.xsl"/>
  <xsl:param name="isc.copyright.leader"/>
  <xsl:param name="isc.copyright.breakline"> \\</xsl:param>

  <xsl:template match="book" mode="docinfo">
    <xsl:apply-imports/>
    <xsl:text>\def\DBKtitle{</xsl:text>
    <xsl:value-of select="info/title"/>
    <xsl:text>}&#10;</xsl:text>

    <xsl:text>\def\DBKcopyright{</xsl:text>
    <xsl:value-of select="$isc.copyright"/>
    <xsl:text>}&#10;</xsl:text>
  </xsl:template>

</xsl:stylesheet>
