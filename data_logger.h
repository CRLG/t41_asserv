#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_


class CDataLogger
{
public:
    CDataLogger();

    void start();
    void stop();
    bool step();
    void print();

    bool m_started;
    long m_start_time;
    long m_index;       // Pointe toujours sur la prochaine ligne
};

#endif // _DATA_LOGGER_H_
