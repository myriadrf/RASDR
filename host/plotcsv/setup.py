#@PydevCodeAnalysisIgnore
#
# Absolutely brilliant documentation:
# http://www.py2exe.org/index.cgi/MatPlotLib

from distutils.core import setup
import py2exe

# replace the PROGRAM name below with the .py of the top-level you want to make an .exe for
# running 'setup.py py2exe' will create an <name>.exe in the dist/

PROGRAM  = ['plotcsv.py']

# Remove the build folder, a bit slower but prevents wierd dependency issues
# Remove the dist folder, it needs to be cleared each time
import shutil
shutil.rmtree("build", ignore_errors=True)
shutil.rmtree("dist",  ignore_errors=True)

data_files = []
includes = ["matplotlib.backends",  "matplotlib.backends.backend_qt4agg",
            "matplotlib.figure","pylab", "numpy"]
excludes = ['bsddb', 'curses', 'pywin.debugger',
            'pywin.debugger.dbgcon', 'pywin.dialogs', 'tcl',
            'Tkconstants', 'Tkinter', 'pydoc', 'doctest', 'test', 'sqlite3'
            ]
packages = ['matplotlib', 'pytz']

# http://stackoverflow.com/questions/323424/py2exe-fails-to-generate-an-executable
#
# may need to add 'MSVCP90.dll', and manually ensure runtime components are installed
# you do this by running 'vcxxx', which I would copy into installation folder before
# .zip.  It is not needed if one has already installed a Microsoft compiler.
# See also: http://www.microsoft.com/en-us/download/details.aspx?id=29

dll_excludes = ['libgdk-win32-2.0-0.dll', 'libgdk_pixbuf-2.0-0.dll',
                'libgobject-2.0-0.dll', 'tcl84.dll',
                'tk84.dll', 'MSVCP90.dll', ]
icon_resources = []
bitmap_resources = []
other_resources = []

# add the mpl mpl-data folder and rc file
import matplotlib as mpl
data_files += mpl.get_py2exe_datafiles()

setup(
    windows=PROGRAM,
                          # compressed and optimize reduce the size
    options = {"py2exe": {"compressed": 2, 
                          "optimize": 2,
                          "includes": includes,
                          "excludes": excludes,
                          "packages": packages,
                          "dll_excludes": dll_excludes,
                          # using 2 to reduce number of files in dist folder
                          # using 1 is not recommended as it often does not work
                          "bundle_files": 2,
                          "dist_dir": 'dist',
                          "xref": False,
                          "skip_archive": False,
                          "ascii": False,
                          "custom_boot_script": '',
                         }
              },

    # using zipfile to reduce number of files in dist
    zipfile = r'lib\library.zip',

    data_files=data_files
)
