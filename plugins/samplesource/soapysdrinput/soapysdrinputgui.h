///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2018 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef PLUGINS_SAMPLESOURCE_SOAPYSDRINPUT_SOAPYSDRINPUTGUI_H_
#define PLUGINS_SAMPLESOURCE_SOAPYSDRINPUT_SOAPYSDRINPUTGUI_H_

#include <QTimer>
#include <QWidget>

#include "plugin/plugininstancegui.h"
#include "util/messagequeue.h"

#include "soapysdrinput.h"

class DeviceUISet;
class ItemSettingGUI;

namespace Ui {
    class SoapySDRInputGui;
}

class SoapySDRInputGui : public QWidget, public PluginInstanceGUI {
    Q_OBJECT

public:
    explicit SoapySDRInputGui(DeviceUISet *deviceUISet, QWidget* parent = 0);
    virtual ~SoapySDRInputGui();
    virtual void destroy();

    void setName(const QString& name);
    QString getName() const;

    virtual void resetToDefaults();
    virtual qint64 getCenterFrequency() const;
    virtual void setCenterFrequency(qint64 centerFrequency);
    virtual QByteArray serialize() const;
    virtual bool deserialize(const QByteArray& data);
    virtual MessageQueue *getInputMessageQueue() { return &m_inputMessageQueue; }
    virtual bool handleMessage(const Message& message);

private:
    void createRangesControl(const SoapySDR::RangeList& rangeList, const QString& text, const QString& unit);
    Ui::SoapySDRInputGui* ui;

    DeviceUISet* m_deviceUISet;
    bool m_forceSettings;
    bool m_doApplySettings;
    SoapySDRInputSettings m_settings;
    QTimer m_updateTimer;
    QTimer m_statusTimer;
    SoapySDRInput* m_sampleSource;
    int m_sampleRate;
    quint64 m_deviceCenterFrequency; //!< Center frequency in device
    int m_lastEngineState;
    MessageQueue m_inputMessageQueue;

    ItemSettingGUI *m_sampleRateGUI;

    void displaySettings();
    void sendSettings();
    void updateSampleRateAndFrequency();
    void updateFrequencyLimits();
    void setCenterFrequencySetting(uint64_t kHzValue);
    void blockApplySettings(bool block);

private slots:
    void handleInputMessages();
    void on_centerFrequency_changed(quint64 value);
    void on_LOppm_valueChanged(int value);
    void sampleRateChanged(double sampleRate);
    void on_dcOffset_toggled(bool checked);
    void on_iqImbalance_toggled(bool checked);
    void on_decim_currentIndexChanged(int index);
    void on_fcPos_currentIndexChanged(int index);
    void on_transverter_clicked();
    void on_startStop_toggled(bool checked);
    void on_record_toggled(bool checked);
    void updateHardware();
    void updateStatus();
};



#endif /* PLUGINS_SAMPLESOURCE_SOAPYSDRINPUT_SOAPYSDRINPUTGUI_H_ */
