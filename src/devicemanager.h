#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>

#include "api/apiinterface.h"
#include "models/devicelistmodel.h"

class DeviceManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)

public:
    explicit DeviceManager(QObject *parent = nullptr);
    ~DeviceManager() override;

    Q_INVOKABLE DeviceListModel *deviceListModel();
    Q_INVOKABLE void initialize();

    // properties
    bool debug() const;

signals:
    Q_INVOKABLE void statisticDataAvailable(const QString &hostname,
                                            const QStringList &labels,
                                            const QList<qreal> &values);

    // properties
    void debugChanged(bool debug);

public slots:
    // add and remove device
    Q_INVOKABLE void addDevice(const QString &hostname);
    Q_INVOKABLE void removeDevice(const QString &hostname);

    // api
    Q_INVOKABLE void connectToWifiAP(const QString &hostname, const QString &ssid, const QString &password);
    Q_INVOKABLE void getCloudInfo(const QString &hostname);
    Q_INVOKABLE void getEnergyDayStat(const QString &hostname,
                                      int month = QDate::currentDate().month(),
                                      int year = QDate::currentDate().year());
    Q_INVOKABLE void getEnergyMonthStat(const QString &hostname,
                                        int year = QDate::currentDate().year());
    Q_INVOKABLE void getEnergyInfo(const QString &hostname);
    Q_INVOKABLE void getSystemInfo(const QString &hostname);
    Q_INVOKABLE void getTime(const QString &hostname);
    Q_INVOKABLE void getTimezone(const QString &hostname);
    Q_INVOKABLE void getWifiAPs(const QString &hostname);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void refresh(const QString &hostname);
    Q_INVOKABLE void restart(const QString &hostname);
    Q_INVOKABLE void reset(const QString &hostname);
    Q_INVOKABLE void resetEnergyStat(const QString &hostname);
    Q_INVOKABLE void setBrightness(const QString &hostname, quint8 brightness);
    Q_INVOKABLE void setCloudServer(const QString &hostname, const QString &url);
    Q_INVOKABLE void setDeviceAlias(const QString &hostname, const QString &alias);
    Q_INVOKABLE void setDeviceMacAddress(const QString &hostname, const QString &mac);
    Q_INVOKABLE void toggleLED(const QString &hostname);
    Q_INVOKABLE void toggleOn(const QString &hostname);
    Q_INVOKABLE void registerDeviceOnCloud(const QString &hostname,
                                           const QString &username,
                                           const QString &password);
    Q_INVOKABLE void sendCmd(const QString &hostname, const QString &cmd);
    Q_INVOKABLE void unregisterDeviceFromCloud(const QString &hostname);

    // properties
    void setDebug(bool debug);

private slots:
    void onConnectionError(const QString &hostname);
    void onReplyAvailable(const QString &hostname,
                          const QString &topic,
                          const QString &cmd,
                          const QJsonObject &payload = QJsonObject());

private:
    // device json helper
    Device *deviceFromJson(const QJsonObject &object);
    QJsonObject deviceToJson(Device *device) const;
    void readDevices();
    void readSettings();
    void writeDevices();
    void writeSettings();


    ApiInterface *m_api;
    DeviceListModel *m_deviceListModel;
    QHash<QString, Device*> m_pendingDevices;
};

#endif // DEVICEMANAGER_H
