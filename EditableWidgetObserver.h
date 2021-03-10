#ifndef EDITABLELABELOBSERVER_H
#define EDITABLELABELOBSERVER_H


class EditableWidgetObserver
{
    class EditableWidget* sub;
public:
    EditableWidgetObserver(class EditableWidget* Sub);
    void EventOnClick();
};

#endif // EDITABLELABELOBSERVER_H
