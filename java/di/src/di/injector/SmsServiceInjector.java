package injector;
import consumer.Consumer;
import consumer.MyDiApp;
import service.SmsServiceImpl;

public class SmsServiceInjector implements MessageServiceInjector {

  @Override
  public Consumer getConsumer() {
    return new MyDiApp(new SmsServiceImpl());
  }
}
