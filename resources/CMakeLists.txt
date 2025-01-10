find_package(Qt6 REQUIRED COMPONENTS LinguistTools)
qt_standard_project_setup(I18N_TRANSLATED_LANGUAGES fr)
qt_add_translations(Password-creator)
target_sources(Password-creator PRIVATE icon.rc)
qt_add_resources(Password-creator imageresources
    PREFIX "/images"
    FILES icon.png
)