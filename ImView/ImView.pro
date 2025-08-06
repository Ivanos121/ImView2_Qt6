QT       += core gui sql webenginewidgets serialport printsupport svgwidgets xml network core5compat dbus

CONFIG += c++20 debug
CONFIG -= qml_debug

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MySortFilterProxyModel.cpp \
    aboutdialog.cpp \
    action_create.cpp \
    archiverchannel.cpp \
    base.cpp \
    branchdrawingdelegate.cpp \
    bvasthread.cpp \
    bvas.cpp \
    checkboxdelegate.cpp \
    checkboxheader.cpp \
    cmydelegate.cpp \
    comboboxbitdelegate.cpp \
    comboboxcurrentdelegate.cpp \
    comboboxdelegate.cpp \
    comboboxerrorarchivedelegate.cpp \
    comboboxmodbusdelegate.cpp \
    comboboxvardelegate.cpp \
    customhelpdelegate.cpp \
    datas.cpp \
    datasource.cpp \
    datasource_el.cpp \
    datasource_file.cpp \
    datasourcebvas.cpp \
    datasourcebvasw.cpp \
    datasourcedigitosc.cpp \
    device.cpp \
    devicedigitosc.cpp \
    digitoscthread.cpp \
    doubledelegate.cpp \
    draw_line.cpp \
    draw_poper.cpp \
    electromagn.cpp \
    fillicondelegate.cpp \
    gridlinedelegate.cpp \
    gybrid_tepl_model.cpp \
    identf.cpp \
    ischodn_dannie.cpp \
    itogs.cpp \
    kalibr.cpp \
    linedelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    model_el.cpp \
    modelidentf.cpp \
    modell.cpp \
    mylabel.cpp \
    mysvgwidget.cpp \
    mytablewidget_2.cpp \
    nabludatel.cpp \
    nabludatel_part.cpp \
    nastroiki.cpp \
    obr_sviaz_tepl.cpp \
    ostat_resurs.cpp \
    paintdelegate.cpp \
    plot.cpp \
    poisk.cpp \
    pushbuttondelegate.cpp \
    settings.cpp \
    settingscanals.cpp \
    spandelegate.cpp \
    spinboxdelegate.cpp \
    start_app.cpp \
    tepl_dannie.cpp \
    tepl_identf.cpp \
    tepl_nabludatel.cpp \
    teplovent.cpp \
    teplschem.cpp \
    treeviewsortdelegate.cpp \
    trend.cpp \
    vent_datas.cpp \
    vent_identf.cpp \
    vent_model.cpp \
    vent_settings.cpp \
    vent_tract.cpp \
    zerocorrector.cpp

HEADERS += \
    Base_tepl_vent.h \
    Identf_kpeff.h \
    MySortFilterProxyModel.h \
    aboutdialog.h \
    action_create.h \
    archiverchannel.h \
    base.h \
    base_tepl.h \
    branchdrawingdelegate.h \
    bvasthread.h \
    bvas.h \
    checkboxdelegate.h \
    checkboxheader.h \
    cmydelegate.h \
    comboboxbitdelegate.h \
    comboboxcurrentdelegate.h \
    comboboxdelegate.h \
    comboboxerrorarchivedelegate.h \
    comboboxmodbusdelegate.h \
    comboboxvardelegate.h \
    crc.h \
    customhelpdelegate.h \
    datas.h \
    datasource.h \
    datasource_el.h \
    datasource_file.h \
    datasourcebvas.h \
    datasourcebvasw.h \
    datasourcedigitosc.h \
    device.h \
    devicedigitosc.h \
    digitoscthread.h \
    doubledelegate.h \
    draw_line.h \
    draw_poper.h \
    electromagn.h \
    fillicondelegate.h \
    gridlinedelegate.h \
    gybrid_tepl_model.h \
    identf.h \
    intens_star_izol.h \
    ischodn_dannie.h \
    itogs.h \
    kalibr.h \
    linedelegate.h \
    mainwindow.h \
    model.h \
    model_el.h \
    modelidentf.h \
    modell.h \
    mylabel.h \
    mysvgwidget.h \
    mytablewidget_2.h \
    nabludatel.h \
    nabludatel_base.h \
    nabludatel_part.h \
    nastroiki.h \
    obr_sviaz_tepl.h \
    ostat_resurs.h \
    paintdelegate.h \
    plot.h \
    poisk.h \
    pushbuttondelegate.h \
    save_progect.h \
    settings.h \
    settingscanals.h \
    spandelegate.h \
    spinboxdelegate.h \
    start_app.h \
    tepl_dannie.h \
    tepl_identf.h \
    tepl_nabludatel.h \
    tepl_struct.h \
    teplovent.h \
    teplschem.h \
    treeviewsortdelegate.h \
    trend.h \
    vent_datas.h \
    vent_identf.h \
    vent_model.h \
    vent_settings.h \
    vent_tract.h \
    version.h \
    version_hash.h \
    zerocorrector.h

FORMS += \
    about_dialog.ui \
    aboutdialog.ui \
    action_create.ui \
    datas.ui \
    draw_line.ui \
    draw_poper.ui \
    electromagn.ui \
    graph_Settings.ui \
    gybrid_tepl_model.ui \
    identf.ui \
    ischodn_dannie.ui \
    itogs.ui \
    kalibr.ui \
    mainwindow.ui \
    nastroiki.ui \
    ostat_resurs.ui \
    poisk.ui \
    settings.ui \
    settingscanals.ui \
    settinsKanals.ui \
    start_app.ui \
    tepl_dannie.ui \
    tepl_identf.ui \
    tepl_nabludatel.ui \
    teplovent.ui \
    teplschem.ui \
    trend.ui \
    vent_datas.ui \
    vent_identf.ui \
    vent_model.ui \
    vent_settings.ui \
    vent_tract.ui

TRANSLATIONS += QtLanguage_ru.ts QtLanguage_en.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lusb-1.0

LIBS += -lquazip1-qt6 -lgsl -lgslcblas

RESOURCES += \
    Images.qrc 

CODECFORSRC     = UTF-8
