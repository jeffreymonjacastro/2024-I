package dbp.e2e.gabriel2;

import dbp.e2e.gabriel2.author.exception.AuthorNotFoundException;
import dbp.e2e.gabriel2.post.exception.PostNotFoundException;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;

// GlobalExceptionHandler is a class that handles exceptions globally for the application.

@ControllerAdvice
public class GlobalExceptionHandler {

    // Exception for not found author
    @ExceptionHandler(AuthorNotFoundException.class)
    public ResponseEntity<String> handleAuthorNotFoundException(AuthorNotFoundException ex) {
        return new ResponseEntity<>(ex.getMessage(), HttpStatus.NOT_FOUND);
    }

    // Exception for not found post
    @ExceptionHandler(PostNotFoundException.class)
    public ResponseEntity<String> handlePostNotFoundException(PostNotFoundException ex) {
        return new ResponseEntity<>(ex.getMessage(), HttpStatus.I_AM_A_TEAPOT);
    }


}
