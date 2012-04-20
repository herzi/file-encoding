import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.FileSystems;
import java.nio.file.Path;

public class Java7Tester {
	public static void main (String[] arguments) {
		Path folder = FileSystems.getDefault().getPath(".");
		try {
			for (Path file: Files.newDirectoryStream(folder)) {
				System.out.println(file.toString());
			}
		} catch (IOException e) {
			System.err.println("cannot open folder");
		}
	}
}
