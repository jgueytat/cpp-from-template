
# check if Doxygen is installed
find_package(Doxygen REQUIRED dot)

if (DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_EXCLUDE_PATTERNS
            "*/.idea/*"
            "*/.git*/*"
            "conanfile.txt")
    set(DOXYGEN_WARN_LOGFILE "DoxygenWarnings.log")
    set(DOXYGEN_HTML_HEADER "./layout/header.html")
    set(DOXYGEN_HTML_EXTRA_STYLESHEET "./layout/style.css")
    set(DOXYGEN_HTML_EXTRA_FILES "./images/logo.jpg")
    doxygen_add_docs(doxygen ALL ${CMAKE_SOURCE_DIR})
else (DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation")
endif (DOXYGEN_FOUND)
