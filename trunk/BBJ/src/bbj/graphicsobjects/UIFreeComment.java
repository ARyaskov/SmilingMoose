/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Polygon;

/**
 *
 * @author Alexander
 */
public class UIFreeComment extends  SceneItem {

    /** Текст комментария. */
    private String m_text;
    
    /**
     * Основной конструктор по умолчанию
     * @param x Координата по оси Х
     * @param y Координата по оси У
     * @param text Текст комментария
     */
    UIFreeComment(int x, int y, String text){
        this.m_coordinates = new Point3D();     // Создаем объект координат
        
        // Задаем значения полям
        this.m_coordinates.setLocation(x, y);   
        this.m_isSelected = false;
        this.m_text = text;
        
        /** Задаем размеры. */
        this.m_height = 80;
        this.m_width = 120;
    }
    
    /**
     * Функция отрисовки комментария
     * @param g Компонент, на котором рисуем
     */
    @Override
    public void draw(Graphics g) {
                
        int i,      // Итератор цикла
            rem;    // Остаток от деления длины строки
        
        // Запомним координаты
        int x = this.m_coordinates.x;
        int y = this.m_coordinates.y;
        int w = this.m_width;
        int h = this.m_height;
           
        Polygon dark = new Polygon();   // Полигон тени
        
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
            g.setColor(Color.getHSBColor(205, 235, 245));
        
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
        for(i=0; i< drawedText.length / 15; i++){
            g.drawChars(drawedText, 0 + i * 15, 
                        15, x + 5, 15 + i * 12 + y);
        }
        
        rem = drawedText.length % 15;   // Вычисляем остаток
        
        // Если остаток есть, дорисовываем символы, которые остались
        if (rem != 0 )
            g.drawChars(drawedText, drawedText.length - rem, rem, 
                        x + 5, 15 + i * 12 + y);
    }
}
