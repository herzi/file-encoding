import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.FileSystems;
import java.nio.file.Path;

public class Java7Tester {
	public static void main (String[] arguments) {
		Path folder = FileSystems.getDefault().getPath(".");
		try {
			for (Path file: Files.newDirectoryStream(folder)) {
				if (file.getFileName().toString().indexOf(".txt") < 0) {
					continue;
				}
                                BufferedReader r = Files.newBufferedReader(file, StandardCharsets.UTF_8);

                                System.out.println("(java7)found: " + r.readLine());
			}
		} catch (IOException e) {
			System.err.println("cannot open folder" + e);
		}
	}
}
