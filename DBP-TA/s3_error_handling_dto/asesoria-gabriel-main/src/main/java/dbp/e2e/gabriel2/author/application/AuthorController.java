package dbp.e2e.gabriel2.author.application;

import dbp.e2e.gabriel2.author.domain.Author;
import dbp.e2e.gabriel2.author.domain.AuthorService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/author")
public class AuthorController {

    @Autowired
    private AuthorService authorService;

    @GetMapping("/saludar")
    public ResponseEntity<String> saludar(){
        return ResponseEntity.ok("Hola te doy la bienvenida a mi web");
    }

    @GetMapping
    public ResponseEntity<List<Author>> authors(){
        return ResponseEntity.ok(authorService.getAll());
    }

    @PostMapping
    public ResponseEntity<Author> newAuthor(@RequestBody Author newAuthor){
        Author author = authorService.createAuthor(newAuthor);
        return ResponseEntity.ok(author);
    }

    @GetMapping("/{id}")
    public ResponseEntity<Author> getAuthorById(@PathVariable Long id){
        return ResponseEntity.ok(authorService.getAuthorById(id));
    }
}
