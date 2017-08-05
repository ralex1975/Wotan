CREATE TABLE [dbo].[index] (
    [id]   BIGINT IDENTITY (1, 1) NOT NULL,
    [type] INT    NOT NULL,
    CONSTRAINT [PK_index] PRIMARY KEY CLUSTERED ([id] ASC),
    CONSTRAINT [FK_index_index_type] FOREIGN KEY ([type]) REFERENCES [dbo].[index_type] ([id])
);

