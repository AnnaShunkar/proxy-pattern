#include <iostream>
using namespace std;

// інтерфейс //
class IMessage {
public:
    virtual void send(const string& text) = 0;
    virtual ~IMessage() = default;
};

// реальний об'єкт //
class RealMessage : public IMessage {
public:
    void send(const string& text) override {
        cout << "Sending message: " << text << endl;
    }
};

// замісник — контролює доступ до реального об'єкта //
class MessageProxy : public IMessage {
private:
    RealMessage* real;
    bool hasAccess;
public:
    MessageProxy(bool access) : hasAccess(access), real(nullptr) {}

    void send(const string& text) override {
        if (hasAccess) {
            if (!real) real = new RealMessage();
            real->send(text);
        }
        else {
            cout << "Access denied. Cannot send message." << endl;
        }
    }
};

int main() {
    // замісник з доступом //
    MessageProxy allowed(true);
    allowed.send("Hello, Anna!");

    // замісник без доступу //
    MessageProxy denied(false);
    denied.send("This message won't be sent.");

    return 0;
}