#ifndef RESULT_H
#define RESULT_H

#include <QString>
#include <QVariant>

struct Result {
    int code;           // 0=success, non-zero=error
    QString message;
    QVariant data;

    Result() : code(0), message("OK") {}
    Result(int c, const QString& msg) : code(c), message(msg) {}
    Result(int c, const QString& msg, const QVariant& d) : code(c), message(msg), data(d) {}

    bool isSuccess() const { return code == 0; }
    bool isError() const { return code != 0; }

    static Result success(const QVariant& data = QVariant()) {
        return Result(0, "OK", data);
    }

    static Result error(int code, const QString& msg) {
        return Result(code, msg);
    }
};

#endif // RESULT_H
