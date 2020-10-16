#ifndef FIXTUREDETAILS_H
#define FIXTUREDETAILS_H

#include <QWidget>

namespace Ui {
class FixtureDetails;
}

class FixtureDetails : public QWidget
{
    Q_OBJECT

public:
    explicit FixtureDetails(QWidget *parent = nullptr);
    ~FixtureDetails();

private:
    Ui::FixtureDetails *ui;
};

#endif // FIXTUREDETAILS_H
