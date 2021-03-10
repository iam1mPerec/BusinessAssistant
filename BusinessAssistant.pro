#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T19:18:09
#
#-------------------------------------------------

QT       += core gui printsupport
QT_DEBUG_PLUGIN

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BusinessAssistant
TEMPLATE = app



# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    NewFacility.cpp \
    NewDocument.cpp \
    CustomListWidget.cpp \
    worker.cpp \
    facility.cpp \
    document.cpp \
    NewWorker.cpp \
    CalendarDate.cpp \
    Calendar.cpp \
    CalendarDateObserver.cpp \
    event.cpp \
    NewEvent.cpp \
    statics.cpp \
    CustomListitem.cpp \
    NewSchedule.cpp \
    schedule.cpp \
    ViewWorker.cpp \
    ViewEvent.cpp \
    EditableWidget.cpp \
    EditableWidgetObserver.cpp \
    EditableDate.cpp \
    EditableLine.cpp \
    EditableText.cpp \
    ViewDocument.cpp \
    ViewSchedule.cpp \
    EditableSchedule.cpp \
    ViewFacility.cpp \
    EventWidget.cpp \
    EventDisplay.cpp \
    CalendarObserver.cpp \
    ClickablePicture.cpp \
    ViewPicture.cpp \
    ViewPrint.cpp \
    PrintFacility.cpp \
    LinkedTablesObserver.cpp \
    PrintListItem.cpp \
    PrintListWidget.cpp \
    CustomButton.cpp \
    FiredDateDialog.cpp \
    FacilityTable.cpp \
    TableItem.cpp \
    DraggableListItem.cpp \
    DraggableListWidget.cpp \
    TableGroup.cpp \
    RandomWorkerList.cpp \
    RandomWorkerItem.cpp \
    TableItemObserver.cpp \
    period.cpp \
    EditableSelection.cpp \
    FormWorker.cpp \
    WorkerFormSelection.cpp \
    HoverableLabel.cpp \
    FormContract.cpp \
    company.cpp \
    FormSchedule.cpp \
    FormFiring.cpp \
    FormEditing.cpp \
    FormLearning.cpp \
    widgetLineEdit.cpp \
    widgetTextEdit.cpp \
    CalendarPrint.cpp \
    CalendarPrintDate.cpp \
    Widget.cpp \
    FormOptions.cpp \
    Settings.cpp

HEADERS += \
        MainWindow.h \
    NewFacility.h \
    NewDocument.h \
    CustomListWidget.h \
    worker.h \
    facility.h \
    document.h \
    NewWorker.h \
    CalendarDate.h \
    Calendar.h \
    CalendarDateObserver.h \
    event.h \
    NewEvent.h \
    statics.h \
    CustomListitem.h \
    NewSchedule.h \
    schedule.h \
    ViewWorker.h \
    ViewEvent.h \
    EditableWidget.h \
    EditableWidgetObserver.h \
    EditableDate.h \
    EditableLine.h \
    EditableText.h \
    ViewDocument.h \
    ViewSchedule.h \
    EditableSchedule.h \
    ViewFacility.h \
    EventWidget.h \
    EventDisplay.h \
    CalendarObserver.h \
    ClickablePicture.h \
    ViewPicture.h \
    ViewPrint.h \
    PrintFacility.h \
    LinkedTablesObserver.h \
    PrintListItem.h \
    PrintListWidget.h \
    CustomButton.h \
    FiredDateDialog.h \
    FacilityTable.h \
    TableItem.h \
    DraggableListItem.h \
    DraggableListWidget.h \
    TableGroup.h \
    RandomWorkerList.h \
    RandomWorkerItem.h \
    TableItemObserver.h \
    period.h \
    EnumDateType.h \
    EnumExpiration.h \
    EnumStates.h \
    EnumCompany.h \
    EnumMaritalStatus.h \
    EnumSex.h \
    EnumFirm.h \
    EditableSelection.h \
    FormWorker.h \
    WorkerFormSelection.h \
    HoverableLabel.h \
    FormContract.h \
    company.h \
    FormSchedule.h \
    FormFiring.h \
    FormEditing.h \
    FormLearning.h \
    widgetLineEdit.h \
    widgetTextEdit.h \
    CalendarPrint.h \
    CalendarPrintDate.h \
    Widget.h \
    FormOptions.h \
    Settings.h

FORMS += \
        MainWindow.ui \
    NewFacility.ui \
    NewDocument.ui \
    NewWorker.ui \
    NewEvent.ui \
    NewSchedule.ui \
    ViewWorker.ui \
    ViewEvent.ui \
    ViewDocument.ui \
    ViewSchedule.ui \
    ViewFacility.ui \
    ViewPicture.ui \
    ViewPrint.ui \
    PrintFacility.ui \
    FiredDateDialog.ui \
    FacilityTable.ui \
    FormWorker.ui \
    WorkerFormSelection.ui \
    FormContract.ui \
    FormSchedule.ui \
    FormFiring.ui \
    FormEditing.ui \
    FormLearning.ui \
    CalendarPrint.ui \
    FormOptions.ui

RESOURCES += \
    assets/res.qrc

CONFIG += static

DISTFILES += \
    assets/window icons/assistant.png \
    assets/window icons/bell.png \
    assets/window icons/calendar.png \
    assets/window icons/doc.png \
    assets/window icons/haus.png \
    assets/window icons/options.png \
    assets/window icons/person.png
