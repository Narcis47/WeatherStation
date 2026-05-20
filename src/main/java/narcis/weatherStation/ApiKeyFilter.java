package narcis.weatherStation;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;

import java.io.IOException;

@Component
public class ApiKeyFilter extends OncePerRequestFilter {
    @Value("${api.key}")
    private String apiKey;

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response,
                                    FilterChain chain) throws ServletException, IOException{
        String path = request.getRequestURI();
        String method = request.getMethod();

        if (method.equals("GET") || path.startsWith("/swagger-ui") || path.startsWith("/v3/api-docs")){
            chain.doFilter(request,response);
            return;
        }

        String key = request.getHeader("X-API-KEY");
        if (apiKey.equals(key)){
            chain.doFilter(request,response);
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.getWriter().write("Invalid or missing API key!");
        }
    }
}
