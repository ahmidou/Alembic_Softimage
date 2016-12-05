# Alembic_Softimage

This is a modified version of the original Alembic Softimage plugin by Autodesk.

the new features are:

* Merge the AbcFramework and the plugin in one dll

* The velocity attribute is now exported as a native alembic geo .v attribute

* The exporter is now reusing samples when possible (needs Softimage 2015 SP2 QFE12)

* updated to Alembic 1.7.0

* Added cmake

The easiest way to build it is to use this automatic builder that will download and build all
the dependencies for you

https://github.com/hybridetech/alembic-build-club
