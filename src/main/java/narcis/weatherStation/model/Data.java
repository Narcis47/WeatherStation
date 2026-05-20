package narcis.weatherStation.model;

import lombok.*;
import org.springframework.data.annotation.Id;
import org.springframework.data.relational.core.mapping.Table;

import java.time.LocalDateTime;


@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor
@Table("weatherdata")
public class Data {
    @Id
    private Long id;
    private Float temp;
    private Float pressure;
    private LocalDateTime updatedAt;
}
