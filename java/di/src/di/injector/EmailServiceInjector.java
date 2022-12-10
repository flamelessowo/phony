package injector;
import consumer.Consumer;
import consumer.MyDiApp;
import service.EmailServiceImpl;

public class EmailServiceInjector implements MessageServiceInjector {
  
  @Override
  public Consumer getConsumer() {
    return new MyDiApp(new EmailServiceImpl());
  }
}
