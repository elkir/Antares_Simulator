// note that the icon used by the Explorer (i.e. the programs icon) is the
// first icon in the executable and the icons are sorted both by their order
// (Win9x) and by alphabetically (!) (NT), so put this icon first and give it
// a name starting with "a"
aaaaa  ICON  "@CMAKE_CURRENT_BINARY_DIR@/win32/updater.ico"

1 VERSIONINFO
FILEVERSION  @ANTARES_VERSION_HI@,@ANTARES_VERSION_LO@,@ANTARES_VERSION_REVISION@,0
PRODUCTVERSION  @ANTARES_VERSION_HI@,@ANTARES_VERSION_LO@,@ANTARES_VERSION_REVISION@,0

BEGIN
  BLOCK "StringFileInfo"
  BEGIN
    BLOCK "040904E4"
    BEGIN
      VALUE "CompanyName", "@ANTARES_PUBLISHER@"
      VALUE "FileDescription", "Antares Study Updater v@ANTARES_VERSION_HI@.@ANTARES_VERSION_LO@.@ANTARES_VERSION_REVISION@"
      VALUE "FileVersion", "@ANTARES_VERSION_HI@.@ANTARES_VERSION_LO@.@ANTARES_VERSION_REVISION@"
      VALUE "InternalName", "Antares Study Updater"
      VALUE "LegalCopyright", "@ANTARES_PUBLISHER@"
      VALUE "OriginalFilename", "antares-@ANTARES_VERSION_HI@.@ANTARES_VERSION_LO@-study-updater.exe"
      VALUE "ProductName", "Antares Study Updater"
      VALUE "ProductVersion", "@ANTARES_VERSION_HI@.@ANTARES_VERSION_LO@.@ANTARES_VERSION_REVISION@"
    END
  END

  BLOCK "VarFileInfo"
  BEGIN
    VALUE "Translation", 0x809, 1200
  END
END

