/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *m_mainWindowGridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QDoubleSpinBox *m_yPos;
    QLabel *label_11;
    QLabel *label_8;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QDoubleSpinBox *m_size;
    QDoubleSpinBox *m_xPos;
    QLabel *label_5;
    QDoubleSpinBox *m_zPos;
    QDoubleSpinBox *m_zVel;
    QDoubleSpinBox *m_bCol;
    QDoubleSpinBox *m_gravity;
    QDoubleSpinBox *m_rCol;
    QLabel *label_7;
    QDoubleSpinBox *m_restitution;
    QLabel *label_14;
    QLabel *label_6;
    QDoubleSpinBox *m_yVel;
    QLabel *label_16;
    QLabel *label_10;
    QLabel *label_19;
    QLabel *label_13;
    QDoubleSpinBox *m_friction;
    QLabel *label_20;
    QComboBox *m_collider;
    QLabel *label_18;
    QPushButton *m_newRigidBody;
    QLabel *label_17;
    QDoubleSpinBox *m_gCol;
    QLabel *label_12;
    QLabel *label_15;
    QDoubleSpinBox *m_xVel;
    QLabel *label;
    QDoubleSpinBox *m_mass;
    QLabel *label_9;
    QLabel *label_21;
    QCheckBox *m_bounds;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 670);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        m_mainWindowGridLayout = new QGridLayout(centralwidget);
        m_mainWindowGridLayout->setObjectName(QStringLiteral("m_mainWindowGridLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_yPos = new QDoubleSpinBox(groupBox);
        m_yPos->setObjectName(QStringLiteral("m_yPos"));
        m_yPos->setMinimum(-100);
        m_yPos->setMaximum(100);
        m_yPos->setValue(5);

        gridLayout->addWidget(m_yPos, 13, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 7, 1, 1, 2);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 3, 1, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 12, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 9, 2, 1, 1);

        m_size = new QDoubleSpinBox(groupBox);
        m_size->setObjectName(QStringLiteral("m_size"));
        m_size->setMinimum(0.1);
        m_size->setValue(1);

        gridLayout->addWidget(m_size, 19, 0, 1, 1);

        m_xPos = new QDoubleSpinBox(groupBox);
        m_xPos->setObjectName(QStringLiteral("m_xPos"));
        m_xPos->setMinimum(-100);
        m_xPos->setMaximum(100);

        gridLayout->addWidget(m_xPos, 13, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 1, 1, 2);

        m_zPos = new QDoubleSpinBox(groupBox);
        m_zPos->setObjectName(QStringLiteral("m_zPos"));
        m_zPos->setMinimum(-100);
        m_zPos->setMaximum(100);

        gridLayout->addWidget(m_zPos, 13, 2, 1, 1);

        m_zVel = new QDoubleSpinBox(groupBox);
        m_zVel->setObjectName(QStringLiteral("m_zVel"));
        m_zVel->setMinimum(-99);

        gridLayout->addWidget(m_zVel, 15, 2, 1, 1);

        m_bCol = new QDoubleSpinBox(groupBox);
        m_bCol->setObjectName(QStringLiteral("m_bCol"));
        m_bCol->setMaximum(1);
        m_bCol->setSingleStep(0.1);
        m_bCol->setValue(1);

        gridLayout->addWidget(m_bCol, 17, 2, 1, 1);

        m_gravity = new QDoubleSpinBox(groupBox);
        m_gravity->setObjectName(QStringLiteral("m_gravity"));
        m_gravity->setMinimum(-100);
        m_gravity->setMaximum(100);
        m_gravity->setSingleStep(0.2);
        m_gravity->setValue(-9.8);

        gridLayout->addWidget(m_gravity, 8, 1, 1, 1);

        m_rCol = new QDoubleSpinBox(groupBox);
        m_rCol->setObjectName(QStringLiteral("m_rCol"));
        m_rCol->setMaximum(1);
        m_rCol->setSingleStep(0.1);

        gridLayout->addWidget(m_rCol, 17, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 1, 1, 2);

        m_restitution = new QDoubleSpinBox(groupBox);
        m_restitution->setObjectName(QStringLiteral("m_restitution"));
        m_restitution->setMaximum(1);
        m_restitution->setValue(0.5);

        gridLayout->addWidget(m_restitution, 9, 1, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 18, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 1, 1, 2);

        m_yVel = new QDoubleSpinBox(groupBox);
        m_yVel->setObjectName(QStringLiteral("m_yVel"));
        m_yVel->setMinimum(-99);

        gridLayout->addWidget(m_yVel, 15, 1, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout->addWidget(label_16, 10, 1, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 6, 1, 1, 2);

        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 22, 1, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 16, 0, 1, 1);

        m_friction = new QDoubleSpinBox(groupBox);
        m_friction->setObjectName(QStringLiteral("m_friction"));
        m_friction->setMaximum(1);
        m_friction->setSingleStep(0.1);

        gridLayout->addWidget(m_friction, 19, 2, 1, 1);

        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout->addWidget(label_20, 25, 1, 1, 1);

        m_collider = new QComboBox(groupBox);
        m_collider->setObjectName(QStringLiteral("m_collider"));

        gridLayout->addWidget(m_collider, 21, 1, 1, 1);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 20, 1, 1, 1);

        m_newRigidBody = new QPushButton(groupBox);
        m_newRigidBody->setObjectName(QStringLiteral("m_newRigidBody"));

        gridLayout->addWidget(m_newRigidBody, 23, 1, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout->addWidget(label_17, 11, 1, 1, 1);

        m_gCol = new QDoubleSpinBox(groupBox);
        m_gCol->setObjectName(QStringLiteral("m_gCol"));
        m_gCol->setMaximum(1);
        m_gCol->setSingleStep(0.1);

        gridLayout->addWidget(m_gCol, 17, 1, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 14, 0, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 18, 1, 1, 1);

        m_xVel = new QDoubleSpinBox(groupBox);
        m_xVel->setObjectName(QStringLiteral("m_xVel"));
        m_xVel->setMinimum(-99);

        gridLayout->addWidget(m_xVel, 15, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 8, 2, 1, 1);

        m_mass = new QDoubleSpinBox(groupBox);
        m_mass->setObjectName(QStringLiteral("m_mass"));
        m_mass->setMinimum(0.1);
        m_mass->setValue(1);

        gridLayout->addWidget(m_mass, 19, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 5, 1, 1, 2);

        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout->addWidget(label_21, 18, 2, 1, 1);

        m_bounds = new QCheckBox(groupBox);
        m_bounds->setObjectName(QStringLiteral("m_bounds"));
        m_bounds->setChecked(true);
        m_bounds->setTristate(false);

        gridLayout->addWidget(m_bounds, 25, 0, 1, 1);


        m_mainWindowGridLayout->addWidget(groupBox, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_mainWindowGridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        label_11->setText(QApplication::translate("MainWindow", "these key presses)", 0));
        label_8->setText(QApplication::translate("MainWindow", "Space : Play/freeze physics", 0));
        label_4->setText(QApplication::translate("MainWindow", "Position", 0));
        label_3->setText(QApplication::translate("MainWindow", "Key Presses: ", 0));
        label_2->setText(QApplication::translate("MainWindow", "Restitution", 0));
        label_5->setText(QApplication::translate("MainWindow", "A : Add random AABB", 0));
        label_7->setText(QApplication::translate("MainWindow", "B : Add bounding sphere", 0));
        label_14->setText(QApplication::translate("MainWindow", "Size", 0));
        label_6->setText(QApplication::translate("MainWindow", "R : reset rigid bodies to 0", 0));
        label_16->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "(Click inside window to use ", 0));
        label_19->setText(QString());
        label_13->setText(QApplication::translate("MainWindow", "Colour", 0));
        label_20->setText(QString());
        m_collider->clear();
        m_collider->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Sphere", 0)
         << QApplication::translate("MainWindow", "AABB", 0)
        );
        label_18->setText(QString());
        m_newRigidBody->setText(QApplication::translate("MainWindow", "Create", 0));
        label_17->setText(QApplication::translate("MainWindow", "Add Object", 0));
        label_12->setText(QApplication::translate("MainWindow", "Velocity", 0));
        label_15->setText(QApplication::translate("MainWindow", "Mass", 0));
        label->setText(QApplication::translate("MainWindow", "Gravity", 0));
        label_9->setText(QApplication::translate("MainWindow", "Arrow keys: Add wind", 0));
        label_21->setText(QApplication::translate("MainWindow", "Friction", 0));
        m_bounds->setText(QApplication::translate("MainWindow", "Bounding Area", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
