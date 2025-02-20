#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QPointer>
#include <QScreen>
#include <QVBoxLayout>

#include "urlhandler.h"


class TestDialog : public QDialog
{
    Q_OBJECT
public:
    TestDialog(QWidget* parent) :  QDialog(parent)
    {
        auto url_handler = UrlHandler::getInstance();
        connect(url_handler, &UrlHandler::labelSet,
                this, &TestDialog::setLabel);

        m_label = new QLabel();
        m_label->setText("Default");
        m_label->setWordWrap(true);

        auto mainlayout = new QVBoxLayout();
        mainlayout->addWidget(m_label);
        mainlayout->addStretch(1);

        setLayout(mainlayout);
    }

    void setLabel(QString label)
    {
        m_label->setText(label);
    }

protected:
    QPointer<QLabel> m_label;
};

#if defined __clang__  // NB defined in Qt Creator; put this first for that reason
    #define COMPILER_IS_CLANG
    #if __clang_major__ >= 10
        #define CLANG_AT_LEAST_10
    #endif
#elif defined __GNUC__  // __GNUC__ is defined for GCC and clang
    #define COMPILER_IS_GCC
    #if __GNUC__ >= 7  // gcc >= 7.0
        #define GCC_AT_LEAST_7
    #endif
#elif defined _MSC_VER
    #define COMPILER_IS_VISUAL_CPP
#endif


#if defined COMPILER_IS_CLANG || defined COMPILER_IS_GCC
    #define VISIBLE_SYMBOL __attribute__ ((visibility ("default")))
#elif defined COMPILER_IS_VISUAL_CPP
    #define VISIBLE_SYMBOL __declspec(dllexport)
#else
    #error "Don't know how to enforce symbol visibility for this compiler!"
#endif


VISIBLE_SYMBOL int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    TestDialog dialog(nullptr);

    dialog.exec();

    return app.exec();
}

#include "main.moc"
