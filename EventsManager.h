class EventsManager{
    public:
        EventsManager();
        init();
        queueEvent(*void event);
        dispatchEvent(*void event);
    private:
        void* eventsQueue[10];
};