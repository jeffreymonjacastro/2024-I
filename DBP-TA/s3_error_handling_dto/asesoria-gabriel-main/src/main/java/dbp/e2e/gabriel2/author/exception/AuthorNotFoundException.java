package dbp.e2e.gabriel2.author.exception;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

//@ResponseStatus(value = HttpStatus.NOT_FOUND)
public class AuthorNotFoundException extends RuntimeException{
    public AuthorNotFoundException(String message) {
        super(message);
    }
}
