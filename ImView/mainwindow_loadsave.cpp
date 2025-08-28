#include <QPropertyAnimation>
#include <QStyle>
#include <QClipboard>
#include <QScreen>
#include <QSpinBox>
#include <QSplitter>
#include <QMessageBox>
#include <QuaZip-Qt6-1.5/quazip/JlCompress.h>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_vector_double.h>
#include <QUndoCommand>
#include <QPixmap>
#include <QSvgRenderer>
#include <QString>
#include <QEvent>
#include <QSettings>
#include <QSqlRecord>
#include <QFileDialog>
#include <QSvgRenderer>
#include <QPainter>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusVariant>
#include <QDBusReply>
#include <QDBusInterface>
#include <QImageWriter>
#include <cxxabi.h>

#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "datas.h"
#include "ui_datas.h"
#include "identf.h"
#include "electromagn.h"
#include "kalibr.h"
#include "teplovent.h"
#include "tepl_dannie.h"
//#include "ui_nastroiki.h"
#include "ui_tepl_dannie.h"
#include "ui_teplovent.h"
#include "ui_datas.h"
#include "vent_model.h"
#include "tepl_identf.h"
#include "settings.h"
#include "start_app.h"
//#include "spandelegate.h"
//#include "branchdrawingdelegate.h"
#include "version.h"
#include "version_hash.h"
#include "Base_tepl_vent.h"
#include "ui_identf.h"

void MainWindow::LoadProject(QString str)
{
    QDir().mkdir("/tmp/imview");
    JlCompress::extractDir(str,"/tmp/imview");
    QFile file(QString("/tmp/imview/project.xml"));
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
    }
    else
    {
        ui->tabWidget->show();
        ui->stackedWidget->show();
        ui->switch_regim_upr->show();
        ui->toolBar->show();
        ui->toolBar_2->show();
        ui->statusbar->show();
        ui->widget_15->hide();
        ui->menu_2->menuAction()->setVisible(true);
        ui->menu_3->menuAction()->setVisible(true);
        ui->menu_4->menuAction()->setVisible(true);
        ui->menu_5->menuAction()->setVisible(true);
        ui->save_file->setVisible(true);
        ui->save_as_file->setVisible(true);
        ui->action_save_graph_file->setVisible(true);
        ui->action_close_progect->setVisible(true);
        ui->action_close_session->setVisible(true);
        ui->print_file->setVisible(true);
        ui->print_preview->setVisible(true);

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name() == "project_name")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            sesion_name_value1->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            identification_switch_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "project_path")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            load_data_ruchn_identf_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            enter_type_experiment_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "project_path_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            read_data_identf_observer_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            data_identification_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_4")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            data_electomagn_process_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_5")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            data_tepl_process_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_6")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            data_vent_process_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_7")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            data_tepl_prognose_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_8")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            data_ostat_tepl_resurs_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_9")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            calculation_mode_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            tuning_coefficient_gd_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            tuning_coefficient_ki_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            tuning_coefficient_gb_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_4")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            tuning_coefficient_kpsi_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_5")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            tuning_coefficient_gp_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_6")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            tuning_coefficient_gpsi_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_10")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            kind_thermal_model_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_11")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            kind_thermal_model_2_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_12")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            kind_thermal_model_4_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_13")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            kind_ventilation_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_14")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            calculation_modes_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_15")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            Heat_processes_accounting_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_16")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            data_approximation_mode_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_17")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            degree_approximating_polynomial_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_18")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            engine_duty_cycle_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "time_cikle")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            time_cycle_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "time_work")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            time_work_in_cycle_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_19")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            time_base_selection_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_20")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            switch_system_electrodrive_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "napragenie")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            enter_voltage_im_mashine_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "moment")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            enter_moment_value->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "start_temp")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            start_tepl_temperature_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_21")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            temperature_regime_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_22")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            temperature_regime_static_value->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_23")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            temperature_regime_dinamic_value->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "time_step")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            time_base_selection_value->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "combobox_24")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ventilation_regime_value->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "combobox_25")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            design_ventilation_system_value->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "pressure")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            barometric_pressure_value->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "sopr_R1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_12->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "sopr_R2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_11->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "ind_L1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_10->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "ind_L2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_9->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "ind_Lm")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_8->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_gd")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_13->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_ki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_16->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_gb")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_14->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_kpsi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_17->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_gp")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_15->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_gpsi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_18->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "time_work")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            time_work_value->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "degree_approximating_polynomial_value")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            degree_approximating_polynomial_value->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "selected_row")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            int attribute_value = attr.value().toInt();
                            ui->widget->ui->tableView->selectRow(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "data_tepl_identification_value")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            data_tepl_identification_value->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "data_vent_identification_value")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            data_vent_identification_value->setText(attribute_value);
                        }
                    }
                }
            }xmlReader.readNext(); // Переходим к следующему элементу файла
        }file.close();
    }


    if(data_vent_identification_value->text() == "Сохранить")
    {
        QFile file3(QString("/tmp/imview/vent_identf.xml"));
        if (!file3.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
        }
        else
        {
            QXmlStreamReader xmlReader3;
            xmlReader3.setDevice(&file3);
            xmlReader3.readNext();

            int koefficient_1_size = 0;
            int koefficient_2_size = 0;
            int koefficient_3_size = 0;
            int koefficient_4_size = 0;

            while(!xmlReader3.atEnd())
            {
                //volatile auto aaaa = xmlReader3.name();
                if(xmlReader3.isStartElement())
                {
                    if(xmlReader3.name() == "Fan_working_set_Qp")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->tableWidget_20->item(0,2)->setText(attribute_value);
                            }
                        }
                    }
                    if(xmlReader3.name() == "Maximum_air_flow_Qmax")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->tableWidget_20->item(1,2)->setText(attribute_value);
                            }
                        }
                    }
                    if(xmlReader3.name() == "Initial_fan_pressure_H0")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->tableWidget_20->item(2,2)->setText(attribute_value);
                            }
                        }
                    }
                    if(xmlReader3.name() == "Fan_working_set_Hp")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->tableWidget_20->item(3,2)->setText(attribute_value);
                            }
                        }
                    }
                    if(xmlReader3.name() == "Total_resistance_of_ventilation_network_Z0")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->tableWidget_20->item(4,2)->setText(attribute_value);
                            }
                        }
                    }
                    if(xmlReader3.name() == "Fan_power_consumption_Pvent")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->tableWidget_20->item(5,2)->setText(attribute_value);
                            }
                        }
                    }

                    if (xmlReader3.name() == "koefficient_1_size")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                koefficient_1_size = attr.value().toInt();
                            }
                        }
                    }

                    for (int i = 0; i < koefficient_1_size; i++)
                    {
                        if (xmlReader3.name() == QString("koefficient_1_") + QString::number(i))
                        {
                            QString attribute_value;

                            // Ищем нужный атрибут
                            foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                            {
                                if (attr.name().toString() == "value")
                                {
                                    attribute_value = attr.value().toString();
                                    break; // нашли нужный атрибут
                                }
                            }

                            // Добавляем новую строку
                            int newRow = ui->tableWidget_20->rowCount();
                            ui->tableWidget_20->insertRow(newRow);

                            //Заполняем ячейку
                            QTableWidgetItem *item = new QTableWidgetItem(attribute_value);
                            ui->tableWidget_20->setItem(newRow, 2, item);
                            QTableWidgetItem *item2 = new QTableWidgetItem("Koefficient_1_" + QString::number(i));
                            ui->tableWidget_20->setItem(newRow, 0, item2);
                            ui->tableWidget_20->setItem(newRow, 1, new QTableWidgetItem("a_1_" + QString::number(i)));
                            ui->tableWidget_20->setItem(newRow, 3, new QTableWidgetItem("--"));

                            ventparam.w_Q_inv_koeffss.append(attribute_value.toDouble());

                            for (int i=1; i<ui->tableWidget_20->columnCount(); i++)
                            {
                                ui->tableWidget_20->item(newRow, i)->setTextAlignment(Qt::AlignCenter);

                            }
                        }
                    }

                    if (xmlReader3.name() == "koefficient_2_size")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                koefficient_2_size = attr.value().toInt();
                            }
                        }
                    }

                    for (int i = 0; i < koefficient_2_size; i++)
                    {
                        if (xmlReader3.name() == "koefficient_2_" + QString::number(i))
                        {
                            QString attribute_value;

                            // Ищем нужный атрибут
                            foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                            {
                                if (attr.name().toString() == "value")
                                {
                                    attribute_value = attr.value().toString();
                                    break; // нашли нужный атрибут
                                }
                            }

                            // Добавляем новую строку
                            int newRow4 = ui->tableWidget_20->rowCount();
                            ui->tableWidget_20->insertRow(newRow4);


                            // Заполняем ячейку
                            QTableWidgetItem *item = new QTableWidgetItem(attribute_value);
                            ui->tableWidget_20->setItem(newRow4, 2, item);
                            ui->tableWidget_20->setItem(newRow4, 0, new QTableWidgetItem("Koefficient_2_" + QString::number(i)));
                            ui->tableWidget_20->setItem(newRow4, 1, new QTableWidgetItem("a_2_" + QString::number(i)));
                            ui->tableWidget_20->setItem(newRow4, 3, new QTableWidgetItem("--"));

                            ventparam.Q_H1_koeffss.append(attribute_value.toDouble());

                            for (int i=1; i<ui->tableWidget_20->columnCount(); i++)
                            {
                                ui->tableWidget_20->item(newRow4, i)->setTextAlignment(Qt::AlignCenter);

                            }
                        }
                    }
                    if (xmlReader3.name() == "koefficient_3_size")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                koefficient_2_size = attr.value().toInt();
                            }
                        }
                    }

                    for (int i = 0; i < koefficient_3_size; i++)
                    {
                        if (xmlReader3.name() == "koefficient_3_" + QString::number(i))
                        {
                            QString attribute_value;

                            // Ищем нужный атрибут
                            foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                            {
                                if (attr.name().toString() == "value")
                                {
                                    attribute_value = attr.value().toString();
                                    break; // нашли нужный атрибут
                                }
                            }

                            // Добавляем новую строку
                            int newRow5 = ui->tableWidget_20->rowCount();
                            ui->tableWidget_20->insertRow(newRow5);


                            // Заполняем ячейку
                            QTableWidgetItem *item = new QTableWidgetItem(attribute_value);
                            ui->tableWidget_20->setItem(newRow5, 2, item);
                            ui->tableWidget_20->setItem(newRow5, 0, new QTableWidgetItem("Koefficient_3_" + QString::number(i)));
                            ui->tableWidget_20->setItem(newRow5, 1, new QTableWidgetItem("a_3_" + QString::number(i)));
                            ui->tableWidget_20->setItem(newRow5, 3, new QTableWidgetItem("--"));

                            ventparam.Q_H2_koeffss.append(attribute_value.toDouble());

                            for (int i=1; i<ui->tableWidget_20->columnCount(); i++)
                            {
                                ui->tableWidget_20->item(newRow5, i)->setTextAlignment(Qt::AlignCenter);

                            }
                        }
                    }
                    for (int i = 0; i < koefficient_4_size; i++)
                    {
                        if (xmlReader3.name() == "koefficient_4_" + QString::number(i))
                        {
                            QString attribute_value;

                            // Ищем нужный атрибут
                            foreach(const QXmlStreamAttribute &attr, xmlReader3.attributes())
                            {
                                if (attr.name().toString() == "value")
                                {
                                    attribute_value = attr.value().toString();
                                    break; // нашли нужный атрибут
                                }
                            }

                            // Добавляем новую строку
                            int newRow6 = ui->tableWidget_20->rowCount();
                            ui->tableWidget_20->insertRow(newRow6);


                            // Заполняем ячейку
                            QTableWidgetItem *item = new QTableWidgetItem(attribute_value);
                            ui->tableWidget_20->setItem(newRow6, 2, item);
                            ui->tableWidget_20->setItem(newRow6, 0, new QTableWidgetItem("Koe4fficient_4_" + QString::number(i)));
                            ui->tableWidget_20->setItem(newRow6, 1, new QTableWidgetItem("a_3_" + QString::number(i)));
                            ui->tableWidget_20->setItem(newRow6, 3, new QTableWidgetItem("--"));

                            ventparam.Q_Pv_koeffss.append(attribute_value.toDouble());

                            for (int i=1; i<ui->tableWidget_20->columnCount(); i++)
                            {
                                ui->tableWidget_20->item(newRow6, i)->setTextAlignment(Qt::AlignCenter);

                            }
                        }
                    }
                }xmlReader3.readNext();
            }
        }file3.close();
    }

    sessionFileName = QFileInfo(str).baseName();

    sesion_name_value1->setText(sessionFileName);
    //setWindowTitle(currentTabText + "@" + QString(item4->text()) + QString(" - ImView"));
    setWindowTitle(currentTabText + "@" + QString(sesion_name_value1->text()) + QString(" - ImView"));
    ui->save_file->setEnabled(true);
    ui->save_as_file->setEnabled(true);
    setCurrentFile(str);
    //ui->widget_2->ui->plot->load();

    loadDefaultPage();
}

void MainWindow::SaveProgectToFile()
{
    QString filter = "Файл конфигурации проекта (*.imview);;Все файлы (*.*)";
    QString str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "../Output", filter);

    QFile file(str);
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QFile files(QString("../save/project.xml"));
    files.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&files);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("project");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("project_name");
    xmlWriter.writeAttribute("value", (sesion_name_value1->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_1");
    xmlWriter.writeAttribute("value", (identification_switch_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path");
    xmlWriter.writeAttribute("value", (load_data_ruchn_identf_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_2");
    xmlWriter.writeAttribute("value", (enter_type_experiment_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path_2");
    xmlWriter.writeAttribute("value", (read_data_identf_observer_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_3");
    xmlWriter.writeAttribute("value", (data_identification_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_4");
    xmlWriter.writeAttribute("value", (data_electomagn_process_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_5");
    xmlWriter.writeAttribute("value", (data_tepl_process_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_6");
    xmlWriter.writeAttribute("value", (data_vent_process_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_7");
    xmlWriter.writeAttribute("value", (data_tepl_prognose_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_8");
    xmlWriter.writeAttribute("value", (data_ostat_tepl_resurs_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_9");
    xmlWriter.writeAttribute("value", (calculation_mode_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_1");
    xmlWriter.writeAttribute("value", (tuning_coefficient_gd_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_2");
    xmlWriter.writeAttribute("value", (tuning_coefficient_ki_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_3");
    xmlWriter.writeAttribute("value", (tuning_coefficient_gb_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_4");
    xmlWriter.writeAttribute("value", (tuning_coefficient_kpsi_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_5");
    xmlWriter.writeAttribute("value", (tuning_coefficient_gp_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_6");
    xmlWriter.writeAttribute("value", (tuning_coefficient_gpsi_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_10");
    xmlWriter.writeAttribute("value", (kind_thermal_model_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_11");
    xmlWriter.writeAttribute("value", (kind_thermal_model_2_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_12");
    xmlWriter.writeAttribute("value", (kind_thermal_model_4_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_13");
    xmlWriter.writeAttribute("value", (kind_ventilation_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_14");
    xmlWriter.writeAttribute("value", (calculation_modes_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_15");
    xmlWriter.writeAttribute("value", (Heat_processes_accounting_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_16");
    xmlWriter.writeAttribute("value", (data_approximation_mode_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_17");
    xmlWriter.writeAttribute("value", (degree_approximating_polynomial_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_18");
    xmlWriter.writeAttribute("value", (engine_duty_cycle_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_cikle");
    xmlWriter.writeAttribute("value", (time_cycle_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_work");
    xmlWriter.writeAttribute("value", (time_work_in_cycle_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_19");
    xmlWriter.writeAttribute("value", (time_base_selection_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_20");
    xmlWriter.writeAttribute("value", (switch_system_electrodrive_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("napragenie");
    xmlWriter.writeAttribute("value", (enter_voltage_im_mashine_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("moment");
    xmlWriter.writeAttribute("value", ( enter_moment_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("start_temp");
    xmlWriter.writeAttribute("value", (start_tepl_temperature_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_21");
    xmlWriter.writeAttribute("value", (temperature_regime_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_22");
    xmlWriter.writeAttribute("value", (temperature_regime_static_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_23");
    xmlWriter.writeAttribute("value", (temperature_regime_dinamic_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_step");
    xmlWriter.writeAttribute("value", (time_base_selection_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_24");
    xmlWriter.writeAttribute("value", (ventilation_regime_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_25");
    xmlWriter.writeAttribute("value", (design_ventilation_system_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("pressure");
    xmlWriter.writeAttribute("value", (barometric_pressure_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("selected_row");
    xmlWriter.writeAttribute("value", QString("%1").arg(QString::number(rowNumber,'f',1)));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("data_tepl_identification_value");
    xmlWriter.writeAttribute("value", (data_tepl_identification_value->text()));

    xmlWriter.writeStartElement("data_vent_identification_value");
    xmlWriter.writeAttribute("value", (data_vent_identification_value->text()));

    if(data_identification_value->text() == "Сохранить")
    {
        xmlWriter.writeStartElement("sopr_R1");
        xmlWriter.writeAttribute("value", (ui->lineEdit_12->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("sopr_R2");
        xmlWriter.writeAttribute("value", (ui->lineEdit_11->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_L1");
        xmlWriter.writeAttribute("value", (ui->lineEdit_10->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_L2");
        xmlWriter.writeAttribute("value", (ui->lineEdit_9->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_Lm");
        xmlWriter.writeAttribute("value", (ui->lineEdit_8->text()));
        xmlWriter.writeEndElement();
    }
    if(calculation_mode_value->text() == "Автоматический")
    {
        xmlWriter.writeStartElement("koeff_gd");
        xmlWriter.writeAttribute("value", (ui->lineEdit_13->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_ki");
        xmlWriter.writeAttribute("value", (ui->lineEdit_16->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gb");
        xmlWriter.writeAttribute("value", (ui->lineEdit_14->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_kpsi");
        xmlWriter.writeAttribute("value", (ui->lineEdit_17->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gp");
        xmlWriter.writeAttribute("value", (ui->lineEdit_15->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gpsi");
        xmlWriter.writeAttribute("value", (ui->lineEdit_18->text()));
        xmlWriter.writeEndElement();
    }
    if(time_base_selection_value->text() == "Фиксированное время")
    {
        xmlWriter.writeStartElement("time_work");
        xmlWriter.writeAttribute("value", (time_work_value->text()));
        xmlWriter.writeEndElement();
    }
    if (data_approximation_mode_value->text() == "Ручной")
    {
        xmlWriter.writeStartElement("degree_approximating_polynomial_value");
        xmlWriter.writeAttribute("value", (degree_approximating_polynomial_value->text()));
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    files.close();   // Закрываем файл

    if(data_identification_value->text() == "Сохранить")
    {
        QFile file2(QString("/home/elf/Видео/ImView2/save/identification.xml"));
        file2.open(QIODevice::WriteOnly);

        //Создаем объект, с помощью которого осуществляется запись в файл
        QXmlStreamWriter xmlWriter2(&file2);
        xmlWriter2.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
        xmlWriter2.writeStartDocument();     // Запускаем запись в документ
        xmlWriter2.writeStartElement("resources");   // Записываем первый элемент с его именем
        xmlWriter2.writeStartElement("identification");  // Записываем тег с именем для первого итема

        xmlWriter2.writeStartElement("stator_resistance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_12->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("rotor_resistance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_11->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("stator_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_10->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("rotor_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_9->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("mutual_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_8->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndDocument();
        file2.close();   // Закрываем файл
    }
    JlCompress::compressDir(str, "../save/");

    sessionFileName = QFileInfo(str).baseName();

    sesion_name_value1->setText(sessionFileName);
}

void MainWindow::on_save_tepl_dannie_clicked()
{
    QString filter = "Файл конфигурации тепловых данных (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "../save", filter);

    // QFile file(QString("/home/elf/ImView/data/tepl.xml"));
    QFile file(str);
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("tepl_dannie");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("sinxr_scorost");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_par_polusov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_osi_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_staniny_v_osnovanii_reber");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_staniny_so_storony_privoda");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_staniny_so_storony_ventilatora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("zazor_megdu_diffuzorom_i_schitom");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kolichestvo_reber_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_rebra_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolschina_rebra_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshny_diametr_ventilatora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshny_diametr_serdechnika_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vnutrenny_diametr_serdechnika_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_pazov_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_shtrichovki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("bolshaya_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("menshaya_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_slica");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_zubca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_zubca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_vitkov_v_obmotke_statore");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_parallelnych_vetvey");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("srednaja_dlina_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_vileta_lobovoi_chasti_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_propitki_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolshina_okraski_obmotki_v_lobovoi_chasty");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolschina_pazovoi_izolacii");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshniy_diametr_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_pazov_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_korotkozamakauchego_kolca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_korotkozamakauchego_kolca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_lopatki_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_lopatki_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_lopatok_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_kachestva_lopatki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolschina_zazora_megdu_statorom_i_rotorom");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kinematicheskaja_vaskost_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chtlyaja_temperatura_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_medi");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_alumimia");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_stali_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_provoda_bez_izolacii");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_izolirovannogo_provoda");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_propitki_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_teploprovodnosty_propitochnogo_sostava");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_teploprovodnosty_izolacii_provodnikov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshnid_diametr_lobovoi_chasti");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefft_teploprovodnosti_okraski_obmotki_v_lobovoi_chasti");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefft_teploprovodnosty_izolacii_provodnikov_2");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolshina_vozdushnych_prosloek");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_zubca_3");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("srednaja_shirina_zubca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_okrugnosti_kasatelnoi_k_dnu_pazov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("bolshaja_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("menshaja_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_paza_2");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_kachestva_lopatki_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shag_reber_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_faz_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_elementarnych_provodnikov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("plotnost_medi");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(63,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaja_teploemkost_medi_obmotki_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(64,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("plotnost_stali");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(65,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaja_teploemkost_medi_stali");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(66,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaje_soprotivlenie_medi");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(67,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("poleznaja_mochnost");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(68,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("napragenie_pitanija");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(69,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_poleznogo_deistvia");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(70,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_mochnosti");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(71,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaje_soprotivlenie_aluminia");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(72,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("srednij_diametr_korotkozamykauchego_kolca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(73,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("obmotochny_koefficient_obmotki_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(74,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_ckosa_pazov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(75,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    //JlCompress::compressDir(str, "/home/elf/ImView/data/");
}

void MainWindow::on_save_Vent_dannie_clicked()
{
    QString filter2 = "Файл конфигурации вентиляционных данных (*.xml);;Все файлы (*.*)";
    QString str2 = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "../save", filter2);

    // QFile file(QString("/home/elf/ImView/data/vent.xml"));
    QFile file(str2);
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("vent_dannie");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("intenal_diameter_ventilator");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(0,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("extenal_diameter_ventilator");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(1,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_lopatki_ventilatora");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(2,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chastota_vrasachenia_ventilatora");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(3,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("plotnost_vozducha");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(4,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("summarnaja_ploschad_otverstiy_v_setke_kogucha");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(5,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Obchaja_ploschad_setki_kogucha");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(6,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_v_meste_povorota_k_rabochemu_kolesu");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(7,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_povorota_potoka_k_vchodnim_kromkam_lopatok_rabochego_kolesa");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(8,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_v_meste_povorota_pered_vchodom_v_megrebernye_kanaly");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(9,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_povorota_potoka_pered_vhodom_v_megrebernye_kanaly");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(10,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_pered_vhodom_v_megrebernye_kanaly");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(11,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_megrebernyh_kanalov_ot_staniny_do_koguha_ventilatora");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(12,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_natekania_potoka_na_rebra_staniny");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(13,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_povorota_potoka_v_megrebernych_kanalah");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(14,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    //JlCompress::compressDir(str, "/home/elf/ImView/data/");
}


void MainWindow::on_load_tepl_dannie_clicked()
{
    QString filter = "Файл конфигурации тепловых данных (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым сохранить данные", "/tmp/imview", filter);
    LoadTeplDannie(str);
}

void MainWindow::LoadTeplDannie(QString str)
{
    //    QDir().mkdir("/tmp/imview");
    //    JlCompress::extractDir(str,"/tmp/imview");


    QFile file(str);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
    }
    else
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name() == "sinxr_scorost")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_par_polusov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_osi_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_staniny_v_osnovanii_reber")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_staniny_so_storony_privoda")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_staniny_so_storony_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "zazor_megdu_diffuzorom_i_schitom")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "kolichestvo_reber_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "visota_rebra_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "tolschina_rebra_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "vneshny_diametr_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "vneshny_diametr_serdechnika_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "vnutrenny_diametr_serdechnika_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_pazov_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_shtrichovki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "bolshaya_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "menshaya_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_slica")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_zubca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_zubca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_vitkov_v_obmotke_statore")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_parallelnych_vetvey")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "srednaja_dlina_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_vileta_lobovoi_chasti_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_propitki_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "tolshina_okraski_obmotki_v_lobovoi_chasty")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "tolschina_pazovoi_izolacii")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "vneshniy_diametr_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_pazov_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_korotkozamakauchego_kolca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_korotkozamakauchego_kolca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_lopatki_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_lopatki_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_lopatok_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_kachestva_lopatki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "tolschina_zazora_megdu_statorom_i_rotorom")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kinematicheskaja_vaskost_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chtlyaja_temperatura_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_medi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_alumimia")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_stali_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_provoda_bez_izolacii")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_izolirovannogo_provoda")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koefficient_propitki_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_teploprovodnosty_propitochnogo_sostava")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_teploprovodnosty_izolacii_provodnikov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "vneshnid_diametr_lobovoi_chasti")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koefft_teploprovodnosti_okraski_obmotki_v_lobovoi_chasti")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->setText(attribute_value);
                            //qDebug() << attribute_value;
                        }
                    }
                }
                else if(xmlReader.name() == "koefft_teploprovodnosty_izolacii_provodnikov_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->setText(attribute_value);
                            //qDebug() << attribute_value;
                        }
                    }
                }
                else if(xmlReader.name() == "tolshina_vozdushnych_prosloek")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_zubca_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "srednaja_shirina_zubca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_okrugnosti_kasatelnoi_k_dnu_pazov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "bolshaja_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "menshaja_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_paza_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_kachestva_lopatki_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shag_reber_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_faz_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_elementarnych_provodnikov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "plotnost_medi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(63,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaja_teploemkost_medi_obmotki_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(64,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "plotnost_stali")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(65,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaja_teploemkost_medi_stali")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(66,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaje_soprotivlenie_medi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(67,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "poleznaja_mochnost")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(68,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "napragenie_pitanija")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(69,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koefficient_poleznogo_deistvia")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(70,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koefficient_mochnosti")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(71,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaje_soprotivlenie_aluminia")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(72,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "srednij_diametr_korotkozamykauchego_kolca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(73,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "obmotochny_koefficient_obmotki_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(74,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koefficient_ckosa_pazov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(75,1)->setText(attribute_value);
                        }
                    }
                }
            }
            xmlReader.readNext(); // Переходим к следующему элементу файла
        }
        file.close(); // Закрываем файл
    }
}

void MainWindow::on_load_Vent_dannie_clicked()
{
    QString filter = "Файл конфигурации тепловых данных (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым сохранить данные", "/tmp/imview", filter);
    LoadVentDannie(str);
}

void MainWindow::LoadVentDannie(QString str)
{
    //    QDir().mkdir("/tmp/imview");
    //    JlCompress::extractDir(str,"/tmp/imview");

    QFile file(str);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
    }
    else
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name() == "intenal_diameter_ventilator")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(0,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "extenal_diameter_ventilator")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(1,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_lopatki_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(2,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chastota_vrasachenia_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(3,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "plotnost_vozducha")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(4,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "summarnaja_ploschad_otverstiy_v_setke_kogucha")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(5,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Obchaja_ploschad_setki_kogucha")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(6,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ploschad_sechenia_v_meste_povorota_k_rabochemu_kolesu")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(7,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ugol_povorota_potoka_k_vchodnim_kromkam_lopatok_rabochego_kolesa")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(8,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ploschad_sechenia_v_meste_povorota_pered_vchodom_v_megrebernye_kanaly")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(9,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ugol_povorota_potoka_pered_vhodom_v_megrebernye_kanaly")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(10,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ploschad_sechenia_pered_vhodom_v_megrebernye_kanaly")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(11,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "Ploschad_sechenia_megrebernyh_kanalov_ot_staniny_do_koguha_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(12,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "Ugol_natekania_potoka_na_rebra_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(13,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "Ugol_povorota_potoka_v_megrebernych_kanalah")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(14,2)->setText(attribute_value);
                        }
                    }
                }
            }
            xmlReader.readNext(); // Переходим к следующему элементу файла
        }
        file.close(); // Закрываем файл
    }
}

void MainWindow::save_file()
{
    sessionFileName = QFileInfo(sesion_name_value1->text()).fileName();

    if (sessionFileName.isEmpty())
    {
        return;
    }

    QFile file(QString("../save/project.xml"));
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("project");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("project_name");
    xmlWriter.writeAttribute("value", (sesion_name_value1->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_1");
    xmlWriter.writeAttribute("value", (identification_switch_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path");
    xmlWriter.writeAttribute("value", (load_data_ruchn_identf_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_2");
    xmlWriter.writeAttribute("value", (enter_type_experiment_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path_2");
    xmlWriter.writeAttribute("value", (read_data_identf_observer_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_3");
    xmlWriter.writeAttribute("value", (data_identification_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_4");
    xmlWriter.writeAttribute("value", (data_electomagn_process_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_5");
    xmlWriter.writeAttribute("value", (data_tepl_process_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_6");
    xmlWriter.writeAttribute("value", (data_vent_process_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_7");
    xmlWriter.writeAttribute("value", (data_tepl_prognose_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_8");
    xmlWriter.writeAttribute("value", (data_ostat_tepl_resurs_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_9");
    xmlWriter.writeAttribute("value", (calculation_mode_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_1");
    xmlWriter.writeAttribute("value", (tuning_coefficient_gd_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_2");
    xmlWriter.writeAttribute("value", (tuning_coefficient_ki_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_3");
    xmlWriter.writeAttribute("value", (tuning_coefficient_gb_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_4");
    xmlWriter.writeAttribute("value", (tuning_coefficient_kpsi_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_5");
    xmlWriter.writeAttribute("value", (tuning_coefficient_gp_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_6");
    xmlWriter.writeAttribute("value", (tuning_coefficient_gpsi_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_10");
    xmlWriter.writeAttribute("value", (kind_thermal_model_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_11");
    xmlWriter.writeAttribute("value", (kind_thermal_model_2_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_12");
    xmlWriter.writeAttribute("value", (kind_thermal_model_4_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_13");
    xmlWriter.writeAttribute("value", (kind_ventilation_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_14");
    xmlWriter.writeAttribute("value", (calculation_modes_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_15");
    xmlWriter.writeAttribute("value", (Heat_processes_accounting_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_16");
    xmlWriter.writeAttribute("value", (data_approximation_mode_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_17");
    xmlWriter.writeAttribute("value", (degree_approximating_polynomial_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_18");
    xmlWriter.writeAttribute("value", (engine_duty_cycle_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_cikle");
    xmlWriter.writeAttribute("value", (time_cycle_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_work");
    xmlWriter.writeAttribute("value", (time_work_in_cycle_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_19");
    xmlWriter.writeAttribute("value", (time_base_selection_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_20");
    xmlWriter.writeAttribute("value", (switch_system_electrodrive_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("napragenie");
    xmlWriter.writeAttribute("value", (enter_voltage_im_mashine_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("moment");
    xmlWriter.writeAttribute("value", ( enter_moment_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("start_temp");
    xmlWriter.writeAttribute("value", (start_tepl_temperature_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_21");
    xmlWriter.writeAttribute("value", (temperature_regime_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_22");
    xmlWriter.writeAttribute("value", (temperature_regime_static_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_23");
    xmlWriter.writeAttribute("value", (temperature_regime_dinamic_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_step");
    xmlWriter.writeAttribute("value", (time_base_selection_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_24");
    xmlWriter.writeAttribute("value", (ventilation_regime_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_25");
    xmlWriter.writeAttribute("value", (design_ventilation_system_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("pressure");
    xmlWriter.writeAttribute("value", (barometric_pressure_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("selected_row");
    xmlWriter.writeAttribute("value", QString::number(rowNumber));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("data_tepl_identification_value");
    xmlWriter.writeAttribute("value", (data_tepl_identification_value->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("data_vent_identification_value");
    xmlWriter.writeAttribute("value", (data_vent_identification_value->text()));


    if(data_identification_value->text() == "Сохранить")
    {
        xmlWriter.writeStartElement("sopr_R1");
        xmlWriter.writeAttribute("value", (ui->lineEdit_12->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("sopr_R2");
        xmlWriter.writeAttribute("value", (ui->lineEdit_11->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_L1");
        xmlWriter.writeAttribute("value", (ui->lineEdit_10->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_L2");
        xmlWriter.writeAttribute("value", (ui->lineEdit_9->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_Lm");
        xmlWriter.writeAttribute("value", (ui->lineEdit_8->text()));
        xmlWriter.writeEndElement();
    }
    if(calculation_mode_value->text() == "Автоматический")
    {
        xmlWriter.writeStartElement("koeff_gd");
        xmlWriter.writeAttribute("value", (ui->lineEdit_13->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_ki");
        xmlWriter.writeAttribute("value", (ui->lineEdit_16->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gb");
        xmlWriter.writeAttribute("value", (ui->lineEdit_14->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_kpsi");
        xmlWriter.writeAttribute("value", (ui->lineEdit_17->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gp");
        xmlWriter.writeAttribute("value", (ui->lineEdit_15->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gpsi");
        xmlWriter.writeAttribute("value", (ui->lineEdit_18->text()));
        xmlWriter.writeEndElement();
    }
    if(time_base_selection_value->text() == "Фиксированное время")
    {
        xmlWriter.writeStartElement("time_work");
        xmlWriter.writeAttribute("value", (time_work_value->text()));
        xmlWriter.writeEndElement();
    }
    if (data_approximation_mode_value->text() == "Ручной")
    {
        xmlWriter.writeStartElement("degree_approximating_polynomial_value");
        xmlWriter.writeAttribute("value", (degree_approximating_polynomial_value->text()));
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    if(data_identification_value->text() == "Сохранить")
    {
        QFile file2(QString("/home/elf/Видео/ImView2/save/identification.xml"));
        file2.open(QIODevice::WriteOnly);

        //Создаем объект, с помощью которого осуществляется запись в файл
        QXmlStreamWriter xmlWriter2(&file2);
        xmlWriter2.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
        xmlWriter2.writeStartDocument();     // Запускаем запись в документ
        xmlWriter2.writeStartElement("resources");   // Записываем первый элемент с его именем
        xmlWriter2.writeStartElement("identification");  // Записываем тег с именем для первого итема

        xmlWriter2.writeStartElement("stator_resistance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_12->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("rotor_resistance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_11->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("stator_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_10->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("rotor_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_9->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("mutual_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_8->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndDocument();
        file2.close();   // Закрываем файл
    }

    ui->widget_2->ui->plot->save();

    JlCompress::compressDir(QString("../Output/") + sessionFileName + ".imview", "../save/");
    ui->save_file->setEnabled(false);
}
