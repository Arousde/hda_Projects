import { Component, OnInit, Input, Output } from '@angular/core';
import { BackendService } from 'src/app/services/backend.service';
import { FsService } from 'src/app/services/fs.service';
import { ExamCard } from 'src/app/models/examCard';

@Component({
  selector: 'app-card-list',
  templateUrl: './card-list.component.html',
  styleUrls: ['./card-list.component.scss']
})
export class CardListComponent implements OnInit {


  cardList: ExamCard[];

  constructor(
    private backendService: BackendService,
    private fsService: FsService
  ) { }

  ngOnInit() {
    this.loadCards();
  }

  loadCards() {
    this.backendService.getCards_RelatedToUser().then((dataList) => {
      this.cardList = dataList;
      console.log(dataList);
    }).catch((err) => {
      this.fsService.writeErrLog(err);
    });
  }

}
