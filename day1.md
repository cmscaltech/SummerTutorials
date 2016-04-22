---
layout: page
title: Getting started with ROOT
subtitle: and make a histogram
---

Today we'll be taking [this raw data](https://github.com/cmscaltech/SummerTutorials/blob/master/Day1/basic.dat) and plotting a histogram in ROOT. 

## Histograms 

A histogram is a graph of a set of observations. Say we have *n* observations of a random variable *xi*, called bins. The number of
occurences of *ni* of *x* in each subinterval is plotted on the y-axis. In the limit of zero bin width, and
infinite observations a histogram exactly replicates a probability density function, or p.d.f. [This](https://github.com/cmscaltech/SummerTutorials/blob/master/Day1/figure_histograms.pdf)
shows the relation between histograms as we change the number of observations and the p.d.f. from which observations are drawn.

To create a histogram from input data text file `Day1/basic.dat` simply run the macro
named `Day1/histogram1D.C`. To run it, begin at a UNIX prompt in the directory `Day1`, open
ROOT, then execute the macro

      $ root -l
      root [0] .x histogram1D.C
      x=-1.102279, y=-1.799389, z=4.452822
      x=1.867178, y=-0.596622, z=3.842313
      x=-0.524181, y=1.868521, z=3.766139
      x=-0.380611, y=0.969128, z=1.084074
      x=0.552454, y=-0.212309, z=0.350281
      root [1]


## Tree

A ROOT TTree (just “tree” for short) is structured container of data, specially designed for collider.
In a collider, we typically are interested in the distribution of certain quantities over many collision
events (or entries). For example, in events with electrons, we may be interested in the distribution
of the an electron’s momentum *|p|*, maybe after requiring that the electron was within “acceptance”
of the detector.

A tree tries to organize this information by effectively linking similar types of information
from different events. This link is called a branch. In the tutorial I showed how to create a tree,
with a few branches for the variables x, y, and z. Sometimes this is called a “flat ntuple” because
none of the information is nested. Here’s a more complicated example, with a nested hierarchy of
information. There is a branch of particles, each particle branch has sub-branches:
http://lcg-heppkg.web.cern.ch/lcg-heppkg/ROOT/eventdata.root