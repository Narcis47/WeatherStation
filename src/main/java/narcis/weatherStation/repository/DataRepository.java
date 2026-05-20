package narcis.weatherStation.repository;

import narcis.weatherStation.model.Data;
import org.springframework.data.repository.CrudRepository;

import java.util.Optional;

public interface DataRepository extends CrudRepository<Data, Long> {
    Optional<Data> findTopByOrderByUpdatedAtDesc();
}
