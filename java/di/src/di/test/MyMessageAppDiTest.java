package test;
import consumer.Consumer;
import injector.EmailServiceInjector;
import injector.SmsServiceInjector;
import injector.MessageServiceInjector;

public class MyMessageAppDiTest {

  public static void main(String[] args) {
    String msg = "Hello bobrow";
    String email = "flamelesscorp@gmail.com";
    String phone = "6661337322";
    MessageServiceInjector injector = null;
    Consumer app = null;

    // Send email
    injector = new EmailServiceInjector();
    app = injector.getConsumer();
    app.processMessages(msg, email);

    // Send sms
    injector = new SmsServiceInjector();
    app = injector.getConsumer();
    app.processMessages(msg, phone);
  }
}
