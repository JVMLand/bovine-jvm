import java.util.*;
import java.time.*;
import java.lang.invoke.*;
import java.lang.ref.*;
public class RuntimeSmoke {
 public static String run() throws Throwable {
  if (!int.class.isPrimitive() || String.class.isPrimitive() || !String[].class.isArray()) throw new AssertionError("Class flags");
  if (!java.lang.reflect.Modifier.isPublic(String.class.getModifiers())) throw new AssertionError("modifiers");
  var weak = new WeakReference<>("live"); if (!"live".equals(weak.get())) throw new AssertionError("reference");
  if (!weak.refersTo("live")) throw new AssertionError("refersTo"); weak.clear(); if (weak.get()!=null || !weak.refersTo(null)) throw new AssertionError("clear");
  var map = new HashMap<String,Integer>(); map.put("a", 2); map.merge("a",3,Integer::sum);
  if (map.get("a")!=5) throw new AssertionError("map");
  if (List.of(1,2,3).stream().mapToInt(Integer::intValue).sum()!=6) throw new AssertionError("stream");
  String text = "日本語😀:" + map.get("a"); if (!text.equals("日本語😀:5")) throw new AssertionError("concat");
  var mh=MethodHandles.lookup().findVirtual(String.class,"length",MethodType.methodType(int.class));
  if ((int)mh.invokeExact("abc")!=3) throw new AssertionError("method handle");
  if (LocalDate.of(2026,9,17).getYear()!=2026) throw new AssertionError("date");
  if (!String.class.getMethod("substring", int.class).invoke("hello", 1).equals("ello")) throw new AssertionError("reflection");
  for (int i=0; i<10000; i++) new String(new char[1024]).hashCode();
  System.gc();
  if (!text.equals("日本語😀:5") || map.get("a")!=5) throw new AssertionError("GC roots");
  System.out.println("Hello from JDK " + System.getProperty("java.version"));
  return "OK " + System.getProperty("java.version");
 }
}
