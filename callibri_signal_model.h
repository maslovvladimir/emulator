#ifndef CALLIBRI_SIGNAL_MODEL_H
#define CALLIBRI_SIGNAL_MODEL_H

#include <QObject>
#include "server/callibri_signal_module.h"
#include "sine_generator.h"

class CallibriSignalModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int samplingFrequencyIndex READ samplingFrequencyIndex WRITE setSamplingFrequencyIndex NOTIFY samplingFrequencyChanged)
    Q_PROPERTY(int gainIndex READ gainIndex WRITE setGainIndex NOTIFY gainIndexChanged)
    Q_PROPERTY(int adcInputIndex READ adcInputIndex WRITE setAdcInputIndex NOTIFY adcInputIndexChanged)
    Q_PROPERTY(int sineAmplitude READ sineAmplitude WRITE setSineAmplitude NOTIFY sineAmplitudeChanged)
    Q_PROPERTY(int sineFrequency READ sineFrequency WRITE setSineFrequency NOTIFY sineFrequencyChanged)
    Q_PROPERTY(int sinePhase READ sinePhase WRITE setSinePhase NOTIFY sinePhaseChanged)
    Q_PROPERTY(int noiseAmplitude READ noiseAmplitude WRITE setNoiseAmplitude NOTIFY noiseAmplitudeChanged)
public:
    explicit CallibriSignalModel(QObject *parent = nullptr);

    void setModule(std::weak_ptr<Nes::CallibriSignalModule>);
    void setSineGenerator(std::weak_ptr<SineGenerator>);

    int samplingFrequencyIndex() const;
    int sineAmplitude() const;
    int sineFrequency() const;
    int sinePhase() const;
    int noiseAmplitude() const;    
    int gainIndex() const;
    int adcInputIndex() const;

public slots:

    void setSamplingFrequencyIndex(int);
    void setSineAmplitude(int);
    void setSineFrequency(int);
    void setSinePhase(int);
    void setNoiseAmplitude(int);    
    void setGainIndex(int gainIndex);
    void setAdcInputIndex(int adcInputIndex);

signals:
    void samplingFrequencyChanged();
    void sineAmplitudeChanged();
    void sineFrequencyChanged();
    void sinePhaseChanged();
    void noiseAmplitudeChanged();
    void gainIndexChanged();
    void adcInputIndexChanged();

private:
    std::weak_ptr<Nes::CallibriSignalModule> modulePtr;
    std::weak_ptr<SineGenerator> sineGeneratorPtr;
    int sineAmpl;
    int sineFreq;
    int sinePh;
    int noiseAmpl;

    void emitAll();
    void updateSignalSource();
    int m_gainIndex;
    int m_adcInputIndex;
};

#endif // CALLIBRI_SIGNAL_MODEL_H
