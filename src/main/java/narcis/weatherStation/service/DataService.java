package narcis.weatherStation.service;

import narcis.weatherStation.model.Data;
import narcis.weatherStation.repository.DataRepository;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.Optional;

@Service
public class DataService {
    private final DataRepository dataRepository;

    public DataService(DataRepository dataRepository) {
        this.dataRepository = dataRepository;
    }

    public Data addData(Float temp, Float pressure){
        Data data = Data.builder().temp(temp).pressure(pressure).updatedAt(LocalDateTime.now()).build();
        return dataRepository.save(data);
    }

    public Optional<Data> getLastData(){
        return dataRepository.findTopByOrderByUpdatedAtDesc();
    }

    public Iterable<Data> getAllData(){
        return dataRepository.findAll();
    }
}
