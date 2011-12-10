/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.*;
import java.awt.Polygon;
import javax.swing.JTextArea;
import java.awt.*;
import bbj.*;

/**
 *
 * @author Alexander
 */
public class UIFreeComment extends  SceneItem {
        
    /** Номер экзампляра данного класса на сцене */
    public static int m_localNumber = 0;
    
    /**
     * Основной конструктор по умолчанию
     * @param x Координата по оси Х
     * @param y Координата по оси У
     * @param text Текст комментария
     */
    public UIFreeComment(int x, int y){

         
        setDefaultName();
        
        this.x=x;
        this.y=y;
        w=120;
        h=80;
        
        // Задаем координаты и размеры
        this.setBounds(this.x,this.y,w,h);
       
        this.m_isSelected = false;      // Не выделен
        
        SceneItemListener listener = new SceneItemListener(this);
                
        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
//        this.addKeyListener(listener);
        this.setToolTipText("Свободный комментарий: " + this.m_text);
    }
    
    /**
     * Метод отрисовки комментария
     * @param g Компонент, на котором рисуем
     */
    @Override
    public void paint(Graphics g) {
      
        super.paint(g);
         
        Graphics2D g2 = (Graphics2D)g;

        int i,      // Итератор цикла
            rem;    // Остаток от деления длины строки
           
        
        /*g2.setColor(new Color(0,0,0,255));
        g2.drawRect(getX(), getY(), getWidth(), getHeight());*/

        Polygon dark = new Polygon();   // Полигон тени

        this.setBounds(this.x,this.y,w+10,h+10);

        // Смещаем координаты     
        x+=10;
        y+=10;

        // Рисуем полигон
        dark.addPoint(x, y);
        dark.addPoint(x + w-20, y);
        dark.addPoint(x + w, y + 20);
        dark.addPoint(x + w, y + h);
        dark.addPoint(x, y + h);

        // Возвращаем координаты обратно
        x-=10;
        y-=10;  

        Color c = new Color(0, 0, 0,125);   // Цвет черный и прозрачный
        Stroke stroke = new BasicStroke(1);
        g2.setStroke(stroke);
        g.setColor(c);                      // Задаем цвет
        g.fillPolygon(dark);                // Заполняем полигон

        Polygon p = new Polygon();          // Полигон комментария

        // Рисуем прямоугольник со скошенным уголком
        p.addPoint(x, y);
        p.addPoint(x + w-20, y);
        p.addPoint(x + w, y + 20);
        p.addPoint(x + w, y + h);
        p.addPoint(x, y + h);

        if (m_isSelected)   // Если выбрали - заливаем желтым   
            g.setColor(Color.getHSBColor(105, 215, 245));
        else                // Иначе, заливаем полигон голубоватым цветом
            g.setColor(new Color(255,210,210));
            //g.setColor(Color.getHSBColor(205, 235, 245));
        
        g.fillPolygon(p);
        
        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g.setColor(Color.black);
        
        g.drawPolygon(p);
        
        g.setColor(Color.black);    // Цвет текста
        
        // Разбиваем текст на массив символов
        char [] drawedText = m_text.toCharArray();
        
        // Рисуем текст по 15 символов в строке
        for(i=0; i< drawedText.length / 15 && i < 4; i++){
            g.drawChars(drawedText, 0 + i * 15, 
                        15, x + 5, 15 + i * 12 + y);
        }
        
        char [] dots = {'.','.','.'};
        
        if (i >= 4)
            g.drawChars(dots, 0, 3, 
                        x + 5, 15 + i * 12 + y);
        
        i++;

        rem = drawedText.length % 15;   // Вычисляем остаток
        
        // Если остаток есть, дорисовываем символы, которые остались
        if (rem != 0 )
            g.drawChars(drawedText, drawedText.length - rem, rem, 
                        x + 5, 15 + i * 12 + y);
        
        if (m_isEdit)
            f.repaint();
    }
    
    @Override
    protected void setDefaultName() {
        m_text = "Комментарий " + Integer.toString(m_localNumber++);
    }
}
