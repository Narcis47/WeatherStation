package narcis.weatherStation.controller;

import narcis.weatherStation.model.Data;
import narcis.weatherStation.service.DataService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/data")
public class DataController {
    private final DataService dataService;
    public record DataRecord(Float temp, Float pressure) {}

    public DataController(DataService dataService) {
        this.dataService = dataService;
    }

    @PostMapping("/add")
    public ResponseEntity<Data> addData(@RequestBody DataRecord record){
        Data data = dataService.addData(record.temp(), record.pressure());
        return ResponseEntity.ok(data);
    }

    @GetMapping("/getLast")
    public ResponseEntity<Data> getLastData(){
        if (dataService.getLastData().isPresent()){
            return ResponseEntity.ok(dataService.getLastData().get());
        }
        return ResponseEntity.badRequest().build();
    }

    @GetMapping("/getAll")
    public ResponseEntity<Iterable<Data>> getAllData(){
        return ResponseEntity.ok(dataService.getAllData());
    }
}
